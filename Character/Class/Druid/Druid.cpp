
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

int Druid::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Druid::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Druid::get_ap_per_strength() const {
    return 1;
}

int Druid::get_ap_per_agi() const {
    return 1;
}

float Druid::global_cooldown() const {
    // Incomplete implementation, is stance specific.
    return 1.5;
}

void Druid::initialize_talents() {

}
