
#include "Warrior.h"
#include "PlayerAction.h"

#include <iostream>

std::string Warrior::get_name(void) const {
    return "Warrior";
}

int Warrior::get_strength_modifier(void) const {
    return 3;
}

int Warrior::get_agility_modifier(void) const {
    return 0;
}

int Warrior::get_stamina_modifier(void) const {
    return 2;
}

int Warrior::get_intellect_modifier(void) const {
    return 0;
}

int Warrior::get_spirit_modifier(void) const {
    return 0;
}

void Warrior::rotation() const {
    std::cout << "Warrior acting\n";
    PlayerAction* new_event = new PlayerAction(this);
    this->get_engine()->add_event(new_event);
}

float Warrior::global_cooldown() const {
    return 1.5;
}
