
#include "Bloodthirst.h"

#include <iostream>

int Bloodthirst::spell_effect(const int resource_level) const {
    // TODO: Roll special hit attack table and deal damage based on outcome.
    // TODO: Apply Flurry buff if critical.
    // TODO: Apply Overpower if dodge.
    std::cout << engine->get_current_priority() <<
                 ": Casting Bloodthirst at " << resource_level << " rage.\n";

    add_spell_cd_event();
    add_gcd_event();

    return resource_cost;
}
