
#include "Warlock.h"

QString Warlock::get_name(void) const {
    return "Warlock";
}

int Warlock::get_strength_modifier(void) const {
    return 0;
}

int Warlock::get_agility_modifier(void) const {
    return 0;
}

int Warlock::get_stamina_modifier(void) const {
    return 1;
}

int Warlock::get_intellect_modifier(void) const {
    return 2;
}

int Warlock::get_spirit_modifier(void) const {
    return 2;
}

int Warlock::get_melee_ap(void) {
    return get_strength();
}

void Warlock::rotation() {
    return;
}

void Warlock::mh_auto_attack(const int) {
    return;
}

void Warlock::oh_auto_attack(const int) {
    return;
}

float Warlock::global_cooldown() const {
    return 1.5;
}
