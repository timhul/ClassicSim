
#include "CooldownReady.h"
#include "Character.h"

#include <iostream>

CooldownReady::CooldownReady(Character* pchar, const float cooldown_ready) {
    this->pchar = pchar;
    this->priority = cooldown_ready;
    this->name = "CooldownReady";
}

void CooldownReady::act(void) {
    //std::cout << this->priority << ": CooldownReady\n";
    pchar->rotation();
}
