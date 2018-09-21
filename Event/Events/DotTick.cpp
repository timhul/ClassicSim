
#include "DotTick.h"
#include "Spell.h"

DotTick::DotTick(Spell* spell, double priority) {
    this->spell = spell;
    this->priority = priority;
    this->name = "DotTick";
}

void DotTick::act(void) {
    spell->perform();
}
