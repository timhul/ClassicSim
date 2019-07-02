#include "Overpower.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Overpower::Overpower(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control) :
    Spell("Overpower", "Assets/items/Inv_sword_05.png", pchar, cooldown_control, RestrictedByGcd::Yes, ResourceType::Rage, 5),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Overpower", 2, DisabledAtZero::No)}),
    warr(pchar),
    spells(spells),
    talent_ranks({0, 2500, 5000})
{}

SpellStatus Overpower::is_ready_spell_specific() const {
    if (warr->in_defensive_stance())
        return SpellStatus::InDefensiveStance;
    if (warr->in_berserker_stance())
        return SpellStatus::InBerserkerStance;
    if (!spells->get_overpower_buff()->is_active())
        return SpellStatus::BuffInactive;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void Overpower::spell_effect() {
    unsigned total_crit = pchar->get_stats()->get_mh_crit_chance() + crit_mod;
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(),
                                                      total_crit,
                                                      false,
                                                      false,
                                                      false,
                                                      true);

    spells->get_overpower_buff()->cancel_buff();
    cooldown->add_gcd_event();
    cooldown->add_spell_cd_event();
    warr->lose_rage(resource_cost);

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_normalized_mh_dmg() + 35);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
}

void Overpower::increase_talent_rank_effect(const QString&, const int curr) {
    crit_mod = talent_ranks[curr];
}

void Overpower::decrease_talent_rank_effect(const QString&, const int curr) {
    crit_mod = talent_ranks[curr];
}
