#include "DotTick.h"

#include "SpellPeriodic.h"

DotTick::DotTick(SpellPeriodic* spell, const double timestamp, const int application_id):
    Event(EventType::DotTick, timestamp),
    spell(spell),
    application_id(application_id)
{}

void DotTick::act() {
    spell->perform_periodic(application_id);
}
