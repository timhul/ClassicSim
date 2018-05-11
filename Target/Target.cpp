
#include "Target.h"

Target::Target(int target_lvl):
    target_lvl(target_lvl),
    target_type(CreatureType::Beast)
{}

int Target::get_lvl(void) const {
    return target_lvl;
}

void Target::set_lvl(int new_tlvl) {
    target_lvl = new_tlvl;
}

int Target::get_defense(void) const {
    return target_lvl * 5;
}

bool Target::is_beast() const {
    return target_type == CreatureType::Beast;
}

bool Target::is_demon() const {
    return target_type == CreatureType::Demon;
}

bool Target::is_dragonkin() const {
    return target_type == CreatureType::Dragonkin;
}

bool Target::is_elemental() const {
    return target_type == CreatureType::Elemental;
}

bool Target::is_giant() const {
    return target_type == CreatureType::Giant;
}

bool Target::is_humanoid() const {
    return target_type == CreatureType::Humanoid;
}

bool Target::is_mechanical() const {
    return target_type == CreatureType::Mechanical;
}

bool Target::is_undead() const {
    return target_type == CreatureType::Undead;
}
