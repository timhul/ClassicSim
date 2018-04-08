
#include "Recklessness.h"

int Recklessness::spell_effect(const int) {
    // TODO: Apply Recklessness buff.
    // TODO: Recklessness buff should make all glancing hits to crits.

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
