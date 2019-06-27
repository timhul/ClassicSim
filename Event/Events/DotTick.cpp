#include "DotTick.h"

#include "Spell.h"

DotTick::DotTick(Spell* spell, const double timestamp):
    Event(EventType::DotTick, timestamp),
    spell(spell)
{}

void DotTick::act() {
    spell->perform_periodic();
}
