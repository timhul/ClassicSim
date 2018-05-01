
#include "PlayerAction.h"
#include "Spells.h"
#include "Engine.h"

PlayerAction::PlayerAction(Spells* spells, const float priority) {
    this->spells = spells;
    this->priority = priority;
    this->name = "PlayerAction";
}

void PlayerAction::act(void) {
    spells->rotation();
}
