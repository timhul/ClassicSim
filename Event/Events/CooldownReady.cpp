
#include "CooldownReady.h"
#include "Spells.h"

CooldownReady::CooldownReady(Spells* spells, const float cooldown_ready) {
    this->spells = spells;
    this->priority = cooldown_ready;
    this->name = "CooldownReady";
}

void CooldownReady::act(void) {
    spells->rotation();
}
