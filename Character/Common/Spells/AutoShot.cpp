#include "AutoShot.h"

#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Equipment.h"
#include "Utils/Check.h"
#include "Weapon.h"

AutoShot::AutoShot(Character* pchar) :
    Spell("Auto Shot",
          "",
          pchar,
          RestrictedByGcd::No,
          0,
          ResourceType::Mana,
          0)
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

void AutoShot::spell_effect() {
    complete_shot();
    calculate_damage(true);
}

void AutoShot::calculate_damage(const bool run_procs) {
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

    double damage_dealt = damage_after_modifiers(pchar->get_random_non_normalized_ranged_dmg());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= pchar->get_stats()->get_ranged_ability_crit_dmg_mod();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_white_critical_effect(run_procs);
        return;
    }

    pchar->ranged_white_hit_effect(run_procs);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double AutoShot::get_next_expected_use() const {
    return next_expected_use;
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

void AutoShot::continue_shot() {
    if (engine->get_current_priority() > next_expected_use)
        next_expected_use = engine->get_current_priority();
}

void AutoShot::complete_shot() {
    last_used = engine->get_current_priority();
    next_expected_use = last_used + pchar->get_stats()->get_ranged_wpn_speed();
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

void AutoShot::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_ranged()->get_value("icon");
    this->cooldown = pchar->get_stats()->get_ranged_wpn_speed();

    reset();
}
