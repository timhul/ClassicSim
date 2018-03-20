
#include "PlayerAction.h"
#include "Character.h"
#include "Engine.h"

#include <iostream>

PlayerAction::PlayerAction(Character *pchar, const float delay) {
    this->pchar = pchar;
    this->priority = pchar->get_engine()->get_current_priority() + delay;
    this->name = "PlayerAction";
}

void PlayerAction::act(void) {
    //std::cout << this->priority << ": PlayerAction\n";
    pchar->rotation();
}
