
#include "Overpower.h"

#include <iostream>

int Overpower::spell_effect(const int resource_level) const {
    // TODO: Roll special hit attack table and deal damage based on outcome.
    // TODO: DODGE/BLOCK/PARRY is not possible for Overpower (only MISS).
    // TODO: Apply Flurry buff if critical.
    std::cout << engine->get_current_priority() <<
                 ": Casting Overpower at " << resource_level << " rage.\n";

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
