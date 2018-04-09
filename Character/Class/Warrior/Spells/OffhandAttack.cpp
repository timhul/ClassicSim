
#include "OffhandAttack.h"
#include "Warrior.h"
#include "Flurry.h"
#include "Equipment.h"
#include "DeepWounds.h"
#include "UnbridledWrath.h"

OffhandAttack::OffhandAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Offhand Attack",
          engine,
          pchar,
          roll,
          (pchar->get_equipment()->is_dual_wielding()) ? pchar->get_equipment()->get_offhand()->get_base_weapon_speed() :
                                                         10000,
          0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    next_expected_use = get_cooldown();
    iteration = 0;
    talent_ranks = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625};
}

int OffhandAttack::spell_effect(const int) {
    // TODO: Check if Windfury is up, roll extra attacks.
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

    float damage_dealt = std::max(1, int(round(pchar->get_random_oh_dmg() * talent_ranks[rank_talent])));
    int uw_proc = pchar->get_unbridled_wrath()->perform(0);

    if (result->is_critical()) {
        damage_dealt *= 2;
        const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
        pchar->melee_critical_effect();
        add_success_stats("Critical", round(damage_dealt), rage_gained);
        return rage_gained + uw_proc;
    }
    if (result->is_glancing()) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(oh_wpn_skill);
        const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
        pchar->get_flurry()->use_charge();
        add_success_stats("Glancing", round(damage_dealt), rage_gained);
        return rage_gained + uw_proc;
    }

    const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
    pchar->get_flurry()->use_charge();
    add_success_stats("Hit", round(damage_dealt), rage_gained);
    return rage_gained + uw_proc;
}

float OffhandAttack::get_next_expected_use() const {
    return next_expected_use;
}

void OffhandAttack::update_next_expected_use(const float haste_change) {
    if (haste_change > 0.01 || haste_change < -0.01) {
        float curr_time = pchar->get_engine()->get_current_priority();
        float remainder_after_haste_change = (next_expected_use - curr_time) / (1 + haste_change);
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
    // TODO: Check if 0 should be used (start attack instantly). Change initializer as well.
    next_expected_use = get_cooldown();
}
