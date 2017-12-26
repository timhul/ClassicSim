
#include "Druid.h"

std::string Druid::get_name(void) const {
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

void Druid::rotation() const {
    return;
}

float Druid::global_cooldown() const {
    // Incomplete implementation, is stance specific.
    return 1.5;
}
