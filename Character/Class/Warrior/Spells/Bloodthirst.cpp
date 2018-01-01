
#include "Bloodthirst.h"

#include <iostream>

int Bloodthirst::spell_effect(const int resource_level) const {
    // TODO: Roll special hit attack table and deal damage based on outcome.
    // TODO: Apply Flurry buff if critical.
    // TODO: Apply Overpower if dodge.
    std::cout << engine->get_current_priority() <<
                 ": Casting Bloodthirst at " << resource_level << " rage.\n";

    // TODO: Roll on special hit table and calculate damage based on melee AP.
    int damage_dealt = 100;

    add_success_stats("Hit", damage_dealt);

    add_spell_cd_event();
    add_gcd_event();

    return resource_cost;
}

void Bloodthirst::add_success_stats(std::string outcome,
                                    const int damage_dealt) const {
    engine->get_statistics()->increment(get_name() + outcome);
    engine->get_statistics()->add("Total Damage", damage_dealt);
    engine->get_statistics()->add(get_name() + outcome + " Damage", damage_dealt);
}
