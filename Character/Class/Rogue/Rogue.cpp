
#include "Rogue.h"

QString Rogue::get_name(void) const {
    return "Rogue";
}

int Rogue::get_strength_modifier(void) const {
    return 1;
}

int Rogue::get_agility_modifier(void) const {
    return 3;
}

int Rogue::get_stamina_modifier(void) const {
    return 1;
}

int Rogue::get_intellect_modifier(void) const {
    return 0;
}

int Rogue::get_spirit_modifier(void) const {
    return 0;
}

int Rogue::get_melee_ap(void) {
    return get_strength() + get_agility();
}

void Rogue::rotation() {
    return;
}

void Rogue::mh_auto_attack() {
    return;
}

void Rogue::oh_auto_attack() {
    return;
}

float Rogue::global_cooldown() const {
    return 1.0;
}
