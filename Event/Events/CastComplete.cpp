#include "CastComplete.h"

#include "Engine.h"
#include "SpellCastingTime.h"

CastComplete::CastComplete(SpellCastingTime* spell, const double timestamp):
    Event(Events::CastComplete, timestamp, "CastComplete"),
    spell(spell)
{}

void CastComplete::act() {
    spell->complete_cast();
}
