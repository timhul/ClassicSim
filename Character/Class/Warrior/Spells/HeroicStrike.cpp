
#include "HeroicStrike.h"

#include <iostream>

int HeroicStrike::spell_effect(const int resource_level) const {
    // TODO: Find weapon skill for mainhand.
    AttackResult* result = roll->get_melee_ability_result(300);

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

    int damage_dealt = pchar->get_mh_dmg() + 138;

    // TODO: Apply Flurry
    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    return resource_cost;
}
