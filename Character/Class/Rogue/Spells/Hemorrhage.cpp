#include "Hemorrhage.h"

#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Rogue.h"
#include "Utils/Check.h"

Hemorrhage::Hemorrhage(Character* pchar) :
    Spell("Hemorrhage", "Assets/spell/Spell_shadow_lifedrain.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 35),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Hemorrhage", 1, DisabledAtZero::Yes),
                   new TalentRequirerInfo("Lethality", 5, DisabledAtZero::No)
                   }),
    SetBonusRequirer({"Bonescythe Armor"}),
    rogue(dynamic_cast<Rogue*>(pchar)),
    statistics_resource(nullptr),
    lethality(1.0),
    bonescythe_energy(0)
{
    this->enabled = false;

    lethality_ranks = {1.0, 1.06, 1.12, 1.18, 1.24, 1.30};
}

void Hemorrhage::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->gain_combo_points(1);

    double damage_dealt = damage_after_modifiers(rogue->get_random_non_normalized_mh_dmg());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= rogue->get_stats()->get_melee_ability_crit_dmg_mod() * lethality;
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());

        rogue->gain_energy(bonescythe_energy);
        statistics_resource->add_resource_gain(ResourceType::Energy, bonescythe_energy);
    }
    else if (result == PhysicalAttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
}

void Hemorrhage::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Lethality")
        lethality = lethality_ranks[curr];
}

void Hemorrhage::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Lethality")
        lethality = lethality_ranks[curr];
}

void Hemorrhage::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Bonescythe Armor") {
        switch (set_bonus) {
        case 4:
            bonescythe_energy = 5;
            break;
        default:
            check(false, "Reached end of switch");
        }
    }
}

void Hemorrhage::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Bonescythe Armor") {
        switch (set_bonus) {
        case 4:
            bonescythe_energy = 0;
            break;
        default:
            check(false, "Reached end of switch");
        }
    }
}

void Hemorrhage::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
