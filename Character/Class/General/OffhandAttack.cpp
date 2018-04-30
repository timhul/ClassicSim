
#include "OffhandAttack.h"
#include "Equipment.h"
#include "Character.h"
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

int OffhandAttack::spell_effect(const int) {
    complete_swing();
    engine->get_statistics()->increment("OH White Total Attempts");

    const int oh_wpn_skill = pchar->get_oh_wpn_skill();
    AttackResult* result = roll->get_melee_hit_result(oh_wpn_skill);

    if (result->is_miss()) {
        add_fail_stats("Miss");
        return 0;
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
        return 0;
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
        return 0;
    }

    float damage_dealt = pchar->get_random_non_normalized_oh_dmg() * 0.5;

    if (result->is_critical()) {
        damage_dealt *= 2;
        pchar->melee_oh_critical_effect();
        add_success_stats("Critical", round(damage_dealt), 0);
        return 0;
    }
    if (result->is_glancing()) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(oh_wpn_skill);
        pchar->melee_oh_hit_effect();
        add_success_stats("Glancing", round(damage_dealt), 0);
        return 0;
    }

    pchar->melee_oh_hit_effect();
    add_success_stats("Hit", round(damage_dealt), 0);
    return 0;
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
    next_expected_use = last_used + pchar->get_oh_wpn_speed();
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
