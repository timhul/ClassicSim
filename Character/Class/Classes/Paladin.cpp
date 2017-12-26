
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

void Paladin::rotation() const {
    return;
}
