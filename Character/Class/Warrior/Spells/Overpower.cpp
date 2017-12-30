
#include "Overpower.h"

#include <iostream>

int Overpower::spell_effect(const int resource_level) const {
    // TODO: Roll special hit attack table and deal damage based on outcome.
    // TODO: DODGE/BLOCK/PARRY is not possible for Overpower (only MISS).
    // TODO: Apply Flurry buff if critical.
    std::cout << engine->get_current_priority() <<
                 ": Casting Overpower at " << resource_level << " rage.\n";

    float cooldown_ready = engine->get_current_priority() + cooldown;
    CooldownReady* new_event = new CooldownReady(pchar, cooldown_ready);
    engine->add_event(new_event);

    return resource_cost;
}
