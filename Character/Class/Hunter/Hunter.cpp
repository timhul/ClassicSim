
#include "Hunter.h"

QString Hunter::get_name(void) const {
    return "Hunter";
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

int Hunter::get_melee_ap(void) {
    return get_strength();
}

void Hunter::rotation() {
    return;
}

void Hunter::mh_auto_attack() {
    return;
}

void Hunter::oh_auto_attack() {
    return;
}

float Hunter::global_cooldown() const {
    return 1.5;
}
