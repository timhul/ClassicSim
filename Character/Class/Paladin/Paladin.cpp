
#include "Paladin.h"

std::string Paladin::get_name(void) const {
    return "Paladin";
}

int Paladin::get_strength_modifier(void) const {
    return 2;
}

int Paladin::get_agility_modifier(void) const {
    return 0;
}

int Paladin::get_stamina_modifier(void) const {
    return 2;
}

int Paladin::get_intellect_modifier(void) const {
    return 0;
}

int Paladin::get_spirit_modifier(void) const {
    return 1;
}

int Paladin::get_melee_ap(void) {
    return get_strength() * 2;
}

void Paladin::rotation() {
    return;
}

void Paladin::mh_auto_attack() {
    return;
}

void Paladin::oh_auto_attack() {
    return;
}

float Paladin::global_cooldown() const {
    return 1.5;
}
