#include "DotTick.h"
#include "NoEffectBuff.h"
#include "OverpowerBuff.h"
#include "Rend.h"
#include "Warrior.h"

Rend::Rend(Character* pchar) :
    Spell("Rend", "Assets/warrior/arms/tier1/Ability_gouge.png", pchar, RestrictedByGcd::Yes, 0, ResourceType::Rage, 10),
    TalentRequirer(3, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar)),
    buff(new NoEffectBuff(pchar, 21, "Rend", "Assets/warrior/arms/tier1/Ability_gouge.png", Hidden::No, Debuff::Yes)),
    damage_remaining(0),
    base_damage(147),
    period_tick(3.0),
    max_ticks(7),
    num_ticks_left(0)
{
    this->talent_ranks = {1.0, 1.15, 1.25, 1.35};
    talent_modifier = talent_ranks[curr_talent_rank];
    buff->enable_buff();
}

Rend::~Rend() {
    delete buff;
}

void Rend::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), 0.0);

    add_gcd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        warr->lose_rage(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    warr->lose_rage(static_cast<unsigned>(resource_cost));
    buff->apply_buff();

    if (num_ticks_left == 0) {
        auto* new_event = new DotTick(this, engine->get_current_priority() + period_tick);
        this->engine->add_event(new_event);
    }

    double duration = period_tick * max_ticks;
    double magic_value = 743.0 / 300000;
    damage_remaining = (base_damage + static_cast<double>(warr->get_avg_mh_damage()) * duration * magic_value) * talent_modifier;

    num_ticks_left = max_ticks;
}

void Rend::perform_periodic() {
    double damage_dealt = round(damage_remaining / num_ticks_left);
    damage_remaining -= damage_dealt;

    double rage_per_tick = resource_cost / max_ticks;
    double execution_time_per_tick = max_ticks / warr->global_cooldown();
    add_hit_dmg(static_cast<int>(damage_dealt), static_cast<int>(round(rage_per_tick)), execution_time_per_tick);

    --num_ticks_left;

    if (num_ticks_left > 0) {
        auto* new_event = new DotTick(this, engine->get_current_priority() + period_tick);
        this->engine->add_event(new_event);
    }
}

void Rend::reset_effect() {
    damage_remaining = 0;
    num_ticks_left = 0;
}

void Rend::increase_talent_rank_effect(const QString&) {
    talent_modifier = talent_ranks[curr_talent_rank];
}

void Rend::decrease_talent_rank_effect(const QString&) {
    talent_modifier = talent_ranks[curr_talent_rank];
}

bool Rend::is_ready_spell_specific() const {
    return !warr->in_berserker_stance();
}