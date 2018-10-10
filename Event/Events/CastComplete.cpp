
#include "CastComplete.h"
#include "SpellCastingTime.h"
#include "Engine.h"

CastComplete::CastComplete(SpellCastingTime *spell, const double priority) {
    this->spell = spell;
    this->priority = priority;
    this->name = "CastComplete";
}

void CastComplete::act() {
    spell->complete_cast();
}
