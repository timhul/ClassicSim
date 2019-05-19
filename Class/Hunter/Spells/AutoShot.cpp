#include "AutoShot.h"

#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "Equipment.h"
#include "Hunter.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"
#include "Weapon.h"

AutoShot::AutoShot(Hunter* pchar) :
    Spell("Auto Shot",
          "",
          pchar,
          RestrictedByGcd::No,
          0,
          ResourceType::Mana,
          0),
    SetBonusRequirer({"Cryptstalker Armor"}),
    hunter(pchar),
    next_expected_use(0),
    iteration(0)
{}

void AutoShot::spell_effect() {
    complete_shot();
    calculate_damage();
}

void AutoShot::calculate_damage() {
    pchar->add_player_reaction_event();

    const int wpn_skill = pchar->get_ranged_wpn_skill();
    const int result = roll->get_ranged_hit_result(wpn_skill, pchar->get_stats()->get_ranged_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_non_normalized_ranged_dmg() + hunter->get_non_normalized_projectile_dmg_bonus());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= pchar->get_stats()->get_ranged_ability_crit_dmg_mod();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_white_hit_effect();
        add_adrenaline_rush_statistics();
        return;
    }

    pchar->ranged_white_hit_effect();
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double AutoShot::get_next_expected_use() const {
    double curr_time = pchar->get_engine()->get_current_priority();
    return next_expected_use > curr_time ? next_expected_use : curr_time;
}

void AutoShot::update_next_expected_use(const double haste_change) {
    double curr_time = pchar->get_engine()->get_current_priority();
    double remainder_after_haste_change = (next_expected_use - curr_time);

    if (remainder_after_haste_change < -0.0001)
        return;

    if (haste_change < 0)
        remainder_after_haste_change *=  (1 + (-1) * haste_change);
    else
        remainder_after_haste_change /=  (1 + haste_change);
    next_expected_use = curr_time + remainder_after_haste_change;
}

void AutoShot::complete_shot() {
    cooldown->last_used = engine->get_current_priority();
    next_expected_use = cooldown->last_used + pchar->get_stats()->get_ranged_wpn_speed();
}

void AutoShot::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_ranged()->get_value("icon");
    this->cooldown->base = pchar->get_stats()->get_ranged_wpn_speed();
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics("Auto Shot", icon);

    reset();
}

void AutoShot::add_adrenaline_rush_statistics() {
    const unsigned before_gain = hunter->get_resource_level(ResourceType::Mana);
    hunter->gain_mana(adrenaline_rush);

    const unsigned delta = hunter->get_resource_level(ResourceType::Mana) - before_gain;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

void AutoShot::reset_shot_timer() {
    next_expected_use = pchar->get_engine()->get_current_priority() + pchar->get_stats()->get_ranged_wpn_speed();
}

bool AutoShot::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int AutoShot::get_next_iteration() {
    return ++iteration;
}

void AutoShot::reset_effect() {
    next_expected_use = 0;
}

void AutoShot::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Cryptstalker Armor") {
        switch (set_bonus) {
        case 6:
            adrenaline_rush = 50;
            break;
        default:
            check(false, "AutoShot::activate_set_bonus_effect reached end of switch");
        }
    }
}

void AutoShot::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == "Cryptstalker Armor") {
        switch (set_bonus) {
        case 6:
            adrenaline_rush = 0;
            break;
        default:
            check(false, "AutoShot::activate_set_bonus_effect reached end of switch");
        }
    }
}
