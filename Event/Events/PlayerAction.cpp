
#include "PlayerAction.h"
#include "Rotation.h"

PlayerAction::PlayerAction(Rotation* rotation, const double priority) {
    this->rotation = rotation;
    this->priority = priority;
    this->name = "PlayerAction";
}

void PlayerAction::act() {
    rotation->perform_rotation();
}
