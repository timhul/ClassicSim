
#include "PlayerAction.h"
#include "Character.h"
#include "Engine.h"

PlayerAction::PlayerAction(Character *pchar, const float delay) {
    this->pchar = pchar;
    this->priority = pchar->get_engine()->get_current_priority() + delay;
    this->name = "PlayerAction";
}

void PlayerAction::act(void) {
    pchar->rotation();
}
