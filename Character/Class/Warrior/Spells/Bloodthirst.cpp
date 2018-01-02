
#include "Bloodthirst.h"

int Bloodthirst::spell_effect(const int) const {
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    int damage_dealt = std::max(1, int(round(pchar->get_melee_ap() * 0.45)));

    // TODO: Apply Flurry
    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_spell_cd_event();
    add_gcd_event();

    return resource_cost;
}
