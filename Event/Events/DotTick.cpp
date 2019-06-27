#include "DotTick.h"

#include "Spell.h"

DotTick::DotTick(Spell* spell, const double timestamp):
    Event(Events::DotTick, timestamp, "DotTick"),
    spell(spell)
{}

void DotTick::act() {
    spell->perform_periodic();
}
