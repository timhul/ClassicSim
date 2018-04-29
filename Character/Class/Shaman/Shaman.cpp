
#include "Shaman.h"

QString Shaman::get_name(void) const {
    return "Shaman";
}

QString Shaman::get_class_color() const {
    return "#0070DE";
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

int Shaman::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Shaman::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Shaman::get_ap_per_strength() const {
    return 1;
}

int Shaman::get_ap_per_agi() const {
    return 1;
}

void Shaman::rotation() {
    return;
}

void Shaman::mh_auto_attack(const int) {
    return;
}

void Shaman::oh_auto_attack(const int) {
    return;
}

float Shaman::global_cooldown() const {
    return 1.5;
}

void Shaman::initialize_talents() {

}
