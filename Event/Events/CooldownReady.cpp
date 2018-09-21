
#include "CooldownReady.h"
#include "Rotation.h"

CooldownReady::CooldownReady(Rotation* rotation, const double cooldown_ready) {
    this->rotation = rotation;
    this->priority = cooldown_ready;
    this->name = "CooldownReady";
}

void CooldownReady::act(void) {
    this->rotation->perform_rotation();
}
