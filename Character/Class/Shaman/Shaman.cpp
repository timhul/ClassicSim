
#include "Shaman.h"

QString Shaman::get_name(void) const {
    return "Shaman";
}

int Shaman::get_strength_modifier(void) const {
    return 1;
}

int Shaman::get_agility_modifier(void) const {
    return 0;
}

int Shaman::get_stamina_modifier(void) const {
    return 1;
}

int Shaman::get_intellect_modifier(void) const {
    return 1;
}

int Shaman::get_spirit_modifier(void) const {
    return 2;
}

int Shaman::get_melee_ap(void) {
    return get_strength() * 2;
}

void Shaman::rotation() {
    return;
}

void Shaman::mh_auto_attack() {
    return;
}

void Shaman::oh_auto_attack() {
    return;
}

float Shaman::global_cooldown() const {
    return 1.5;
}
