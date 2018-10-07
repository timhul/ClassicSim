
#include "ResourceGain.h"
#include "Spell.h"
#include "Engine.h"

ResourceGain::ResourceGain(Spell *spell, const double priority) {
    this->spell = spell;
    this->priority = priority;
    this->name = "ResourceGain";
}

void ResourceGain::act() {
    spell->perform_periodic();
    // TODO: Consider adding PlayerAction event.
}
