
#include "Whirlwind.h"

#include <iostream>

int Whirlwind::spell_effect(const int resource_level) const {
    // TODO: Roll special hit attack table and deal damage based on outcome.
    // TODO: Apply Flurry buff if critical.
    // TODO: Apply Overpower if dodge.
    std::cout << engine->get_current_priority() <<
                 ": Casting Whirlwind at " << resource_level << " rage.\n";

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
