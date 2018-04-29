
#include "Mage.h"

QString Mage::get_name(void) const {
    return "Mage";
}

QString Mage::get_class_color() const {
    return "#69CCF0";
}

int Mage::get_strength_modifier(void) const {
    return 0;
}

int Mage::get_agility_modifier(void) const {
    return 0;
}

int Mage::get_stamina_modifier(void) const {
    return 0;
}

int Mage::get_intellect_modifier(void) const {
    return 3;
}

int Mage::get_spirit_modifier(void) const {
    return 2;
}

int Mage::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Mage::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Mage::get_ap_per_strength() const {
    return 1;
}

int Mage::get_ap_per_agi() const {
    return 1;
}

void Mage::rotation() {
    return;
}

void Mage::mh_auto_attack(const int) {
    return;
}

void Mage::oh_auto_attack(const int) {
    return;
}

float Mage::global_cooldown() const {
    return 1.5;
}

void Mage::initialize_talents() {

}
