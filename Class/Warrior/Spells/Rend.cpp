#include "Rend.h"

#include "Buff.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "NoEffectUniqueDebuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Rend::Rend(Warrior* pchar, WarriorSpells* spells) :
    SpellPeriodic("Rend", "Assets/ability/Ability_gouge.png", pchar,
                  new NoEffectUniqueDebuff(pchar, Priority::Trash, 21, "Rend", "Assets/ability/Ability_gouge.png", Hidden::No),
                  RestrictedByGcd::Yes, ResourceType::Rage, 3.0, 10),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Rend", 3, DisabledAtZero::No)}),
    warr(pchar),
    spells(spells),
    damage_remaining(0),
    base_damage(147),
    period_tick(3.0),
    max_ticks(7),
    num_ticks_left(0),
    talent_ranks({1.0, 1.15, 1.25, 1.35})
{
    enabled = true;
    marker_buff->enable_buff();
    talent_modifier = talent_ranks[0];
}

Rend::~Rend() {
    delete marker_buff;
}

bool Rend::check_application_success() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), 0.0);

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        warr->lose_rage(resource_cost);
        return false;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        spells->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return false;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return false;
    }

    warr->lose_rage(resource_cost);
    return true;
}

void Rend::new_application_effect() {
    double duration = period_tick * max_ticks;
    double magic_value = 743.0 / 300000;
    damage_remaining = (base_damage + static_cast<double>(warr->get_avg_mh_damage()) * duration * magic_value) * talent_modifier;

    num_ticks_left = max_ticks;
}

void Rend::refresh_effect() {
    new_application_effect();
}

void Rend::tick_effect() {
    const double damage_dealt = round(damage_remaining / num_ticks_left);
    damage_remaining -= damage_dealt;

    const double rage_per_tick = double(resource_cost) / max_ticks;
    const double execution_time_per_tick = max_ticks / warr->global_cooldown();
    add_hit_dmg(static_cast<int>(damage_dealt), rage_per_tick, execution_time_per_tick);

    --num_ticks_left;

    if (num_ticks_left > 0)
        add_next_tick();
}

void Rend::reset_effect() {
    damage_remaining = 0;
    num_ticks_left = 0;
}

void Rend::increase_talent_rank_effect(const QString&, const int curr) {
    talent_modifier = talent_ranks[curr];
}

void Rend::decrease_talent_rank_effect(const QString&, const int curr) {
    talent_modifier = talent_ranks[curr];
}

SpellStatus Rend::is_ready_spell_specific() const {
    if (warr->in_berserker_stance())
        return SpellStatus::InBerserkerStance;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}
