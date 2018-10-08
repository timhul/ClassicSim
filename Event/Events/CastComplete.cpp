
#include "CastComplete.h"
#include "Spell.h"
#include "Engine.h"

CastComplete::CastComplete(Spell *spell, const double priority) {
    this->spell = spell;
    this->priority = priority;
    this->name = "CastComplete";
}

void CastComplete::act() {
    spell->perform_periodic();
}
