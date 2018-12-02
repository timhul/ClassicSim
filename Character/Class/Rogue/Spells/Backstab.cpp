#include "Backstab.h"
#include "CharacterStats.h"
#include "Rogue.h"
#include "Equipment.h"
#include "Weapon.h"

Backstab::Backstab(Character* pchar) :
    Spell("Backstab", "Assets/ability/Ability_backstab.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 60),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Backstab", 3, DisabledAtZero::No)}),
    rogue(dynamic_cast<Rogue*>(pchar))
{
    talent_ranks = {0.0, 0.1, 0.2, 0.3};
    crit_modifier = talent_ranks[0];
}

bool Backstab::is_ready_spell_specific() const {
    return rogue->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::DAGGER;
}

void Backstab::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance() + crit_modifier);

    add_gcd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = damage_after_modifiers(rogue->get_random_normalized_mh_dmg() * 1.5 + 165.0);

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * rogue->get_ability_crit_dmg_mod());
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == AttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->gain_combo_points(1);
}

void Backstab::increase_talent_rank_effect(const int curr, const QString&) {
    crit_modifier = talent_ranks[curr];
}

void Backstab::decrease_talent_rank_effect(const int curr, const QString&) {
    crit_modifier = talent_ranks[curr];
}
