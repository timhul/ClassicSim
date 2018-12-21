#include "OffhandAttack.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Weapon.h"

OffhandAttack::OffhandAttack(Character* pchar) :
    Spell("Offhand Attack",
          "Assets/items/Inv_sword_04.png",
          pchar,
          RestrictedByGcd::No,
          (pchar->get_equipment()->get_offhand() != nullptr) ? pchar->get_equipment()->get_offhand()->get_base_weapon_speed() :
                                                                10000,
          ResourceType::Rage,
          0),
    offhand_penalty(0.5)
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

void OffhandAttack::extra_attack() {
    calculate_damage(false);
}

void OffhandAttack::spell_effect() {
    complete_swing();
    calculate_damage(true);
}

void OffhandAttack::calculate_damage(const bool run_procs) {
    const int oh_wpn_skill = pchar->get_oh_wpn_skill();
    const int result = roll->get_melee_hit_result(oh_wpn_skill, pchar->get_stats()->get_oh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_non_normalized_oh_dmg() * offhand_penalty);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);

        pchar->melee_oh_white_critical_effect(run_procs);
        return;
    }

    pchar->melee_oh_white_hit_effect(run_procs);

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(oh_wpn_skill);
        add_glancing_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        return;
    }

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double OffhandAttack::get_next_expected_use() const {
    return next_expected_use;
}

void OffhandAttack::update_next_expected_use(const double haste_change) {
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

void OffhandAttack::complete_swing() {
    last_used = engine->get_current_priority();
    next_expected_use = last_used + pchar->get_stats()->get_oh_wpn_speed();
}

void OffhandAttack::reset_swingtimer() {
    next_expected_use = pchar->get_engine()->get_current_priority() + pchar->get_stats()->get_oh_wpn_speed();
}

bool OffhandAttack::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int OffhandAttack::get_next_iteration() {
    return ++iteration;
}

void OffhandAttack::reset_effect() {
    next_expected_use = 0;
}

