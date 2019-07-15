#include "CastComplete.h"

#include "CastingTimeRequirer.h"
#include "Engine.h"

CastComplete::CastComplete(CastingTimeRequirer* cast, const double timestamp):
    Event(EventType::CastComplete, timestamp),
    cast(cast)
{}

void CastComplete::act() {
    cast->complete_cast();
}
