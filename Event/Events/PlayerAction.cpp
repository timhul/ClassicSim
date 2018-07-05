
#include "PlayerAction.h"
#include "Rotation.h"

PlayerAction::PlayerAction(Rotation* rotation, const float priority) {
    this->rotation = rotation;
    this->priority = priority;
    this->name = "PlayerAction";
}

void PlayerAction::act(void) {
    rotation->perform_rotation();
}
