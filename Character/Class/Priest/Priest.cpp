
#include "Priest.h"

QString Priest::get_name(void) const {
    return "Priest";
}

int Priest::get_strength_modifier(void) const {
    return 0;
}

int Priest::get_agility_modifier(void) const {
    return 0;
}

int Priest::get_stamina_modifier(void) const {
    return 0;
}

int Priest::get_intellect_modifier(void) const {
    return 2;
}

int Priest::get_spirit_modifier(void) const {
    return 3;
}

int Priest::get_melee_ap(void) {
    return get_strength();
}

void Priest::rotation() {
    return;
}

void Priest::mh_auto_attack(const int) {
    return;
}

void Priest::oh_auto_attack(const int) {
    return;
}

float Priest::global_cooldown() const {
    return 1.5;
}
