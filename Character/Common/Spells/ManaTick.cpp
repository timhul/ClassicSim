#include "Mana.h"
#include "ManaTick.h"

ManaTick::ManaTick(Character* pchar, class Mana* mana)
    :
      Spell("Mana Tick", "no-icon", pchar, RestrictedByGcd::No, 0.0, ResourceType::Mana, 0),
      mana(mana)
{}

void ManaTick::spell_effect() {
    assert(false);
}

void ManaTick::perform_periodic() {
    mana->tick_mana();
}
