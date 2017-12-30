
#include "PlayerAction.h"

#include <iostream>

PlayerAction::PlayerAction(Class* pclass, const float delay) {
    this->pclass = pclass;
    this->priority = pclass->get_engine()->get_current_priority() + delay;
}

void PlayerAction::act(void) {
    std::cout << this->priority << ": PlayerAction\n";
    pclass->rotation();
}
