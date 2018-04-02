
#include "Druid.h"

QString Druid::get_name(void) const {
    return "Druid";
}

QString Druid::get_class_color() const {
    return "#FF7D0A";
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

int Druid::get_ap_per_strength() const {
    return 1;
}

int Druid::get_ap_per_agi() const {
    return 1;
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

void Druid::initialize_talents() {

}

void Druid::reset_spells() const {

}
