
#include "Character.h"

Race* Character::get_race(void) {
    return this->race;
}

Class* Character::get_class(void) {
    return this->pclass;
}

void Character::let_player_act(void) {
    this->pclass->rotation();
}
