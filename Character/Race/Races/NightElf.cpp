
#include "NightElf.h"

int NightElf::get_race_int() const {
    return Races::NightElf;
}

QString NightElf::get_name() const {
    return "Night Elf";
}

unsigned NightElf::get_base_strength() const {
    return 17;
}

unsigned NightElf::get_base_agility() const {
    return 25;
}

unsigned NightElf::get_base_stamina() const {
    return 19;
}

unsigned NightElf::get_base_intellect() const {
    return 20;
}

unsigned NightElf::get_base_spirit() const {
    return 20;
}

double NightElf::get_int_multiplier() const {
    return 1.0;
}

double NightElf::get_spirit_multiplier() const {
    return 1.0;
}

int NightElf::get_axe_bonus() const {
    return 0;
}

int NightElf::get_sword_bonus() const {
    return 0;
}

int NightElf::get_mace_bonus() const {
    return 0;
}

int NightElf::get_bow_bonus() const {
    return 0;
}

int NightElf::get_gun_bonus() const {
    return 0;
}

int NightElf::get_thrown_bonus() const {
    return 0;
}
