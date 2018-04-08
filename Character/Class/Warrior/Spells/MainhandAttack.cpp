
#include "MainhandAttack.h"
#include "Warrior.h"
#include "Flurry.h"
#include "Equipment.h"
#include "DeepWounds.h"

MainhandAttack::MainhandAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Mainhand Attack",
          engine,
          pchar,
          roll,
          (pchar->get_equipment()->get_mainhand() != nullptr) ? pchar->get_equipment()->get_mainhand()->get_base_weapon_speed() :
                                                                10000,
          0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    next_expected_use = get_cooldown();
    iteration = 0;
}

int MainhandAttack::spell_effect(const int) {
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

    int damage_dealt = std::max(1, pchar->get_mh_dmg());

    if (result->is_critical()) {
        damage_dealt *= 2;
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        pchar->critical_effect();
        add_success_stats("Critical", damage_dealt, rage_gained);
        return rage_gained;
    }
    if (result->is_glancing()) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(mh_wpn_skill);
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        pchar->get_flurry()->use_charge();
        add_success_stats("Glancing", damage_dealt, rage_gained);
        return rage_gained;
    }

    const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
    pchar->get_flurry()->use_charge();
    add_success_stats("Hit", damage_dealt, rage_gained);
    return rage_gained;
}

float MainhandAttack::get_next_expected_use() const {
    return next_expected_use;
}

void MainhandAttack::update_next_expected_use(const float haste_change) {
    if (haste_change > 0.01 || haste_change < -0.01) {
        float curr_time = pchar->get_engine()->get_current_priority();
        float remainder_after_haste_change = (next_expected_use - curr_time) / (1 + haste_change);
        next_expected_use = curr_time + remainder_after_haste_change;
    }
    else {
        next_expected_use = last_used + pchar->get_mh_wpn_speed();
    }
}

bool MainhandAttack::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int MainhandAttack::get_next_iteration() {
    return ++iteration;
}

void MainhandAttack::reset_effect() {
    // TODO: Check if 0 should be used (start attack instantly). Change initializer as well.
    next_expected_use = get_cooldown();
}
