#include "PlayerAction.h"

#include "Character.h"

PlayerAction::PlayerAction(Character* pchar, const double priority) {
    this->pchar = pchar;
    this->priority = priority;
    this->name = "PlayerAction";
}

void PlayerAction::act() {
    pchar->perform_rotation();
}
