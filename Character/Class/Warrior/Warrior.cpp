
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

void Warrior::rotation() {
    std::cout << "Warrior acting\n";
    // Remember to add PlayerAction event with current priority for any melee hit event
    // This is to use resources as soon as they become available.
    // if (this->get_engine()->on_gcd() or not enough resource for ability usage)  { return }
    // The checks above at the minimum are required to handle this.
    // Some classes will need "special gcd" for stances, totems, shapeshifts, auras(?), etc.
    // Fury warriors need this for overpower modelling.

    if (!is_melee_attacking())
        start_attack();

    // TODO: Check if execute is available. Requires target health.

    if (bt->is_available(rage))
        rage -= bt->perform(rage);

    PlayerAction* new_event = new PlayerAction(this);
    this->get_engine()->add_event(new_event);
}

float Warrior::global_cooldown() const {
    return 1.5;
}

bool Warrior::is_dual_wielding(void) {
    // TODO: Check if one-handed weapons equipped in both weapon slots.
    return true;
}

int Warrior::get_curr_rage() const {
    return this->rage;
}
