#include "ResourceGain.h"

#include "Spell.h"

ResourceGain::ResourceGain(Spell* spell, const double timestamp):
    Event(Events::ResourceGain, timestamp, "ResourceGain"),
    spell(spell)
{}

void ResourceGain::act() {
    spell->perform_periodic();
}
