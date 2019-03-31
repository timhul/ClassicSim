#include "ResourceGain.h"

#include "Character.h"
#include "Engine.h"
#include "Spell.h"

ResourceGain::ResourceGain(Character* pchar, Spell *spell, const double timestamp) {
    this->pchar = pchar;
    this->spell = spell;
    this->priority = timestamp;
    this->name = "ResourceGain";
}

void ResourceGain::act() {
    spell->perform_periodic();
}
