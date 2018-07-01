
#include "Recklessness.h"
#include "Warrior.h"

void Recklessness::spell_effect() {
    // TODO: Apply Recklessness buff.
    // TODO: Recklessness buff should make all glancing hits to crits.

    add_gcd_event();
    add_spell_cd_event();

    dynamic_cast<Warrior*>(pchar)->lose_rage(resource_cost);
}
