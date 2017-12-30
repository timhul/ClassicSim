
#include "Recklessness.h"

#include <iostream>

int Recklessness::spell_effect(const int resource_level) const {
    // TODO: Apply Recklessness buff.
    // TODO: Recklessness buff should make all glancing hits to crits.
    std::cout << engine->get_current_priority() <<
                 ": Casting Recklessness at " << resource_level << " rage.\n";

    float cooldown_ready = engine->get_current_priority() + cooldown;
    CooldownReady* new_event = new CooldownReady(pchar, cooldown_ready);
    engine->add_event(new_event);

    return resource_cost;
}
