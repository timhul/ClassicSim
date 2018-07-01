
#include "OffhandAttack.h"
#include "Equipment.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Weapon.h"
#include <QDebug>

OffhandAttack::OffhandAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Offhand Attack",
          engine,
          pchar,
          roll,
          (pchar->get_equipment()->get_offhand() != nullptr) ? pchar->get_equipment()->get_offhand()->get_base_weapon_speed() :
                                                                10000,
          0)
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

void OffhandAttack::spell_effect() {
    complete_swing();
    calculate_damage();
}

void OffhandAttack::calculate_damage() {
    const int oh_wpn_skill = pchar->get_oh_wpn_skill();
    const int result = roll->get_melee_hit_result(oh_wpn_skill);

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }
    // TODO: Apply Overpower
    if (result == AttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        return;
    }

    float damage_dealt = pchar->get_random_non_normalized_oh_dmg() * 0.5;

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= 2;
        pchar->melee_oh_white_critical_effect();
        add_crit_dmg(round(damage_dealt));
        return;
    }
    if (result == AttackResult::GLANCING) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(oh_wpn_skill);
        pchar->melee_oh_white_hit_effect();
        add_glancing_dmg(round(damage_dealt));
        return;
    }

    pchar->melee_oh_white_hit_effect();
    add_hit_dmg(round(damage_dealt));
}

float OffhandAttack::get_next_expected_use() const {
    return next_expected_use;
}

void OffhandAttack::update_next_expected_use(const float haste_change) {
    assert(haste_change > 0.001 || haste_change < -0.001);

    float curr_time = pchar->get_engine()->get_current_priority();
    float remainder_after_haste_change = (next_expected_use - curr_time);

    if (remainder_after_haste_change < -0.0001)
        return;

    if (haste_change < 0)
        remainder_after_haste_change *=  (1 + (-1) * haste_change);
    else
        remainder_after_haste_change /=  (1 + haste_change);

    next_expected_use = curr_time + remainder_after_haste_change;
}

void OffhandAttack::complete_swing() {
    next_expected_use = last_used + pchar->get_stats()->get_oh_wpn_speed();
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

float OffhandAttack::get_cooldown() {
    qDebug() << "Do not use get_cooldown() for white hit spells, use get_next_expected_use() instead.";
    assert(false);

    return 1.0;
}

void OffhandAttack::extra_attack() {
    calculate_damage();
}
