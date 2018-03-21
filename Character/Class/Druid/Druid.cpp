
#include "Druid.h"

QString Druid::get_name(void) const {
    return "Druid";
}

int Druid::get_strength_modifier(void) const {
    return 1;
}

int Druid::get_agility_modifier(void) const {
    return 0;
}

int Druid::get_stamina_modifier(void) const {
    return 0;
}

int Druid::get_intellect_modifier(void) const {
    return 2;
}

int Druid::get_spirit_modifier(void) const {
    return 2;
}

int Druid::get_melee_ap(void) {
    return get_strength();
}

void Druid::rotation() {
    return;
}

void Druid::mh_auto_attack(const int) {
    return;
}

void Druid::oh_auto_attack(const int) {
    return;
}

float Druid::global_cooldown() const {
    // Incomplete implementation, is stance specific.
    return 1.5;
}
