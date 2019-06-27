#include "CastComplete.h"

#include "Engine.h"
#include "SpellCastingTime.h"

CastComplete::CastComplete(SpellCastingTime* spell, const double timestamp):
    Event(EventType::CastComplete, timestamp),
    spell(spell)
{}

void CastComplete::act() {
    spell->complete_cast();
}
