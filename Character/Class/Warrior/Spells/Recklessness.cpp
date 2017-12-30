
#include "Recklessness.h"

#include <iostream>

int Recklessness::spell_effect(const int resource_level) const {
    // TODO: Apply Recklessness buff.
    // TODO: Recklessness buff should make all glancing hits to crits.
    std::cout << engine->get_current_priority() <<
                 ": Casting Recklessness at " << resource_level << " rage.\n";

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
