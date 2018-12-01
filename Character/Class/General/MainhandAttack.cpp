
#include "MainhandAttack.h"
#include "Equipment.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Weapon.h"
#include <QDebug>

MainhandAttack::MainhandAttack(Character* pchar) :
    Spell("Mainhand Attack",
          "Assets/items/Inv_axe_01.png",
          pchar,
          RestrictedByGcd::No,
          (pchar->get_equipment()->get_mainhand() != nullptr) ? pchar->get_equipment()->get_mainhand()->get_base_weapon_speed() :
                                                                10000,
          ResourceType::Rage,
          0)
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

void MainhandAttack::extra_attack() {
    calculate_damage(false);
}

void MainhandAttack::spell_effect() {
    complete_swing();
    calculate_damage(true);
}

void MainhandAttack::calculate_damage(const bool run_procs) {
    const int mh_wpn_skill = pchar->get_mh_wpn_skill();
    const int result = roll->get_melee_hit_result(mh_wpn_skill, pchar->get_stats()->get_mh_crit_chance());

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        return;
    }

    double damage_dealt = pchar->get_random_non_normalized_mh_dmg();

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->melee_mh_white_critical_effect(run_procs);
        return;
    }

    pchar->melee_mh_white_hit_effect(run_procs);

    if (result == AttackResult::GLANCING) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(mh_wpn_skill);
        add_glancing_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        return;
    }

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double MainhandAttack::get_next_expected_use() const {
    return next_expected_use;
}

void MainhandAttack::update_next_expected_use(const double haste_change) {
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

void MainhandAttack::complete_swing() {
    last_used = engine->get_current_priority();
    next_expected_use = last_used + pchar->get_stats()->get_mh_wpn_speed();
}

void MainhandAttack::reset_swingtimer() {
    next_expected_use = pchar->get_engine()->get_current_priority() + pchar->get_stats()->get_mh_wpn_speed();
}


bool MainhandAttack::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int MainhandAttack::get_next_iteration() {
    return ++iteration;
}

void MainhandAttack::reset_effect() {
    next_expected_use = 0;
}
