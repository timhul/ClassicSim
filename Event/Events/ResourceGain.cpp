#include "ResourceGain.h"

#include "Spell.h"

ResourceGain::ResourceGain(Spell* spell, const double timestamp):
    Event(EventType::ResourceGain, timestamp),
    spell(spell)
{}

void ResourceGain::act() {
    spell->perform_periodic();
}
