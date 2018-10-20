
#include "ResourceGain.h"
#include "Spell.h"
#include "Engine.h"
#include "Character.h"

ResourceGain::ResourceGain(Character* pchar, Spell *spell, const double priority) {
    this->pchar = pchar;
    this->spell = spell;
    this->priority = priority;
    this->name = "ResourceGain";
}

void ResourceGain::act() {
    spell->perform_periodic();
    pchar->add_player_reaction_event();
}
