#include "PlayerAction.h"

#include "Character.h"

PlayerAction::PlayerAction(Character* pchar, const double timestamp) {
    this->pchar = pchar;
    this->priority = timestamp;
    this->name = "PlayerAction";
}

void PlayerAction::act() {
    pchar->perform_rotation();
}
