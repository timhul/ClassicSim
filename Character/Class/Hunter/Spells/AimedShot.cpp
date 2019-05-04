#include "AimedShot.h"

#include "AutoShot.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Hunter.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

AimedShot::AimedShot(Hunter* pchar) :
    SpellCastingTime("Aimed Shot",
                     "Assets/items/Inv_spear_07.png",
                     pchar,
                     RestrictedByGcd::Yes,
                     6.0,
                     ResourceType::Mana,
                     310,
                     3000),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Aimed Shot", 1, DisabledAtZero::Yes),
                                                new TalentRequirerInfo("Efficiency", 5, DisabledAtZero::No),
                                                new TalentRequirerInfo("Mortal Shots", 5, DisabledAtZero::No)}),
    SetBonusRequirer({"Cryptstalker Armor"}),
    hunter(pchar),
    base_casting_time_ms(3000)
{
    this->enabled = false;
    resource_base = resource_cost;
    efficiency_ranks = {
        1.0, 0.98, 0.96, 0.94, 0.92, 0.90
    };
    mortal_shots_bonus = 0.0;
    mortal_shots_ranks = {
        0.0, 0.06, 0.12, 0.18, 0.24, 0.30
    };
}

void AimedShot::spell_effect() {
    pchar->get_spells()->stop_attack();
    add_gcd_event();
    casting_time_ms = static_cast<unsigned>(round(base_casting_time_ms / pchar->get_stats()->get_ranged_attack_speed_mod()));
    start_cast();
}

void AimedShot::complete_cast_effect() {
    pchar->get_spells()->start_attack();
    add_spell_cd_event();

    pchar->lose_mana(resource_cost);
    const int wpn_skill = pchar->get_ranged_wpn_skill();
    const int result = roll->get_ranged_ability_result(wpn_skill, pchar->get_stats()->get_ranged_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_normalized_ranged_dmg() + 600 + hunter->get_normalized_projectile_dmg_bonus());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= pchar->get_stats()->get_ranged_ability_crit_dmg_mod() + mortal_shots_bonus;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_yellow_critical_effect(true);
        add_adrenaline_rush_statistics();
        return;
    }

    pchar->ranged_yellow_hit_effect(true);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

void AimedShot::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics("Aimed Shot", icon);
}

void AimedShot::add_adrenaline_rush_statistics() {
    const unsigned before_gain = hunter->get_resource_level(ResourceType::Mana);
    hunter->gain_mana(adrenaline_rush);

    const unsigned delta = hunter->get_resource_level(ResourceType::Mana) - before_gain;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

void AimedShot::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Efficiency")
        resource_cost = static_cast<unsigned>(round(resource_base * efficiency_ranks[curr]));
    if (talent_name == "Mortal Shots")
        mortal_shots_bonus = mortal_shots_ranks[curr];
}

void AimedShot::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Efficiency")
        resource_cost = static_cast<unsigned>(round(resource_base * efficiency_ranks[curr]));
    if (talent_name == "Mortal Shots")
        mortal_shots_bonus = mortal_shots_ranks[curr];
}

void AimedShot::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Cryptstalker Armor") {
        switch (set_bonus) {
        case 6:
            adrenaline_rush = 50;
            break;
        case 8:
            resource_cost -= 20;
            break;
        default:
            check(false, "AimedShot::activate_set_bonus_effect reached end of switch");
        }
    }
}

void AimedShot::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Cryptstalker Armor") {
        switch (set_bonus) {
        case 6:
            adrenaline_rush = 0;
            break;
        case 8:
            resource_cost += 20;
            break;
        default:
            check(false, "AimedShot::activate_set_bonus_effect reached end of switch");
        }
    }
}
