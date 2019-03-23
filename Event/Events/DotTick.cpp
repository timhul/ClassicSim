#include "DotTick.h"

#include "Spell.h"

DotTick::DotTick(Spell* spell, double timestamp) {
    this->spell = spell;
    this->priority = timestamp;
    this->name = "DotTick";
}

void DotTick::act() {
    spell->perform_periodic();
}
