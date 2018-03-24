
#include "Mage.h"

QString Mage::get_name(void) const {
    return "Mage";
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

int Mage::get_melee_ap(void) {
    return get_strength();
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
