
#include "CooldownReady.h"
#include "Character.h"

CooldownReady::CooldownReady(Character* pchar, const float cooldown_ready) {
    this->pchar = pchar;
    this->priority = cooldown_ready;
    this->name = "CooldownReady";
}

void CooldownReady::act(void) {
    pchar->rotation();
}
