
#include "Overpower.h"

#include <iostream>

int Overpower::spell_effect(const int) const {
    // TODO: Use special hit table where dodge and parry are not possible.
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }

    int damage_dealt = pchar->get_mh_dmg() + 35;

    // TODO: Apply Flurry
    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
