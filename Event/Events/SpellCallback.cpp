#include "SpellCallback.h"

#include "SealOfCommand.h"

SpellCallback::SpellCallback(SealOfCommand* spell, const double timestamp):
    Event(EventType::SpellCallback, timestamp),
    spell(spell)
{}

void SpellCallback::act() {
    spell->run_proc();
}
