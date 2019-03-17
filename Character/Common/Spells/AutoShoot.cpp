#include "AutoShoot.h"

#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Equipment.h"
#include "Weapon.h"

AutoShoot::AutoShoot(Character* pchar) :
    Spell("Auto-Shoot",
          "Assets/items/Inv_weapon_bow_11.png",
          pchar,
          RestrictedByGcd::No,
          (pchar->get_equipment()->get_ranged() != nullptr) ? pchar->get_equipment()->get_ranged()->get_base_weapon_speed() :
                                                              10000,
          ResourceType::Mana,
          0),
    paused(false)
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

void AutoShoot::spell_effect() {
    complete_shot();
    calculate_damage(true);
}

void AutoShoot::calculate_damage(const bool run_procs) {
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
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_white_critical_effect(run_procs);
        return;
    }

    pchar->ranged_white_hit_effect(run_procs);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double AutoShoot::get_next_expected_use() const {
    return next_expected_use;
}

void AutoShoot::update_next_expected_use(const double haste_change) {
    assert(haste_change > 0.001 || haste_change < -0.001);

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

void AutoShoot::pause_shot() {
    paused = true;
}

void AutoShoot::continue_shot(const double offset) {
    paused = false;
    next_expected_use += offset;
}

void AutoShoot::complete_shot() {
    last_used = engine->get_current_priority();
    next_expected_use = last_used + pchar->get_stats()->get_ranged_wpn_speed();
}

void AutoShoot::reset_shot_timer() {
    next_expected_use = pchar->get_engine()->get_current_priority() + pchar->get_stats()->get_ranged_wpn_speed();
}

bool AutoShoot::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int AutoShoot::get_next_iteration() {
    return ++iteration;
}

void AutoShoot::reset_effect() {
    next_expected_use = 0;
    paused = false;
}
