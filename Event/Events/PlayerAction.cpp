
#include "PlayerAction.h"
#include <iostream>

PlayerAction::PlayerAction(const Class* pclass) {
    this->pclass = pclass;
    this->priority = pclass->get_engine()->get_current_priority() + pclass->global_cooldown();
}

void PlayerAction::act(void) {
    std::cout << "PlayerAction\n";
    if (!this->pclass) {
        std::cerr << "Null pointer for pclass for PlayerAction";
        exit(-1);
    }
    pclass->rotation();
}
