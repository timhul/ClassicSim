
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
    update_next_expected_use(0.0);
    // TODO: Check if Windfury is up, roll extra attacks.
    engine->get_statistics()->increment("MH White Total Attempts");

    const int mh_wpn_skill = pchar->get_mh_wpn_skill();
    AttackResult* result = roll->get_melee_hit_result(mh_wpn_skill);

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

    float damage_dealt = std::max(1, pchar->get_random_mh_dmg());

    if (result->is_critical()) {
        damage_dealt *= 2;
        pchar->melee_critical_effect();
        add_success_stats("Critical", round(damage_dealt), 0);
        return 0;
    }
    if (result->is_glancing()) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(mh_wpn_skill);
        add_success_stats("Glancing", round(damage_dealt), 0);
        return 0;
    }

    add_success_stats("Hit", round(damage_dealt), 0);
    return 0;
}

float OffhandAttack::get_next_expected_use() const {
    return next_expected_use;
}

void OffhandAttack::update_next_expected_use(const float haste_change) {
    if (haste_change > 0.01 || haste_change < -0.01) {
        float curr_time = pchar->get_engine()->get_current_priority();
        float remainder_after_haste_change = (next_expected_use - curr_time);
        if (haste_change < 0)
            remainder_after_haste_change *=  (1 + (-1)*haste_change);
        else
            remainder_after_haste_change /=  (1 + haste_change);
        next_expected_use = curr_time + remainder_after_haste_change;
    }
    else {
        next_expected_use = last_used + pchar->get_oh_wpn_speed();
    }
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
