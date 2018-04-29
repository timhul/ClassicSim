
#include "Hunter.h"

QString Hunter::get_name(void) const {
    return "Hunter";
}

QString Hunter::get_class_color() const {
    return "#ABD473";
}

int Hunter::get_strength_modifier(void) const {
    return 0;
}

int Hunter::get_agility_modifier(void) const {
    return 3;
}

int Hunter::get_stamina_modifier(void) const {
    return 1;
}

int Hunter::get_intellect_modifier(void) const {
    return 0;
}

int Hunter::get_spirit_modifier(void) const {
    return 1;
}

int Hunter::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Hunter::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Hunter::get_ap_per_strength() const {
    return 1;
}

int Hunter::get_ap_per_agi() const {
    return 1;
}

void Hunter::rotation() {
    return;
}

void Hunter::mh_auto_attack(const int) {
    return;
}

void Hunter::oh_auto_attack(const int) {
    return;
}

float Hunter::global_cooldown() const {
    return 1.5;
}

void Hunter::initialize_talents() {

}
