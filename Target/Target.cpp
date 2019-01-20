#include "Target.h"

#include <QDebug>

#include "Mechanics.h"

Target::Target(int target_lvl):
    target_lvl(target_lvl),
    target_armor(Mechanics(nullptr).get_boss_base_armor()),
    target_type(CreatureType::Beast)
{
    creature_type_strings = {{CreatureType::Beast, "Beast"},
                             {CreatureType::Demon, "Demon"},
                             {CreatureType::Dragonkin, "Dragonkin"},
                             {CreatureType::Elemental, "Elemental"},
                             {CreatureType::Giant, "Giant"},
                             {CreatureType::Humanoid, "Humanoid"},
                             {CreatureType::Mechanical, "Mechanical"},
                             {CreatureType::Undead, "Undead"}};

    string_to_creature_type = {{"Beast", CreatureType::Beast},
                               {"Demon", CreatureType::Demon},
                               {"Dragonkin", CreatureType::Dragonkin},
                               {"Elemental", CreatureType::Elemental},
                               {"Giant", CreatureType::Giant},
                               {"Humanoid", CreatureType::Humanoid},
                               {"Mechanical", CreatureType::Mechanical},
                               {"Undead", CreatureType::Undead}};
}

int Target::get_lvl() const {
    return target_lvl;
}

void Target::set_lvl(int new_tlvl) {
    target_lvl = new_tlvl;
}

int Target::get_defense() const {
    return target_lvl * 5;
}

int Target::get_armor() const {
    return target_armor < 0 ? 0 : target_armor;
}

void Target::set_armor(const int armor) {
    this->target_armor = armor;
}

void Target::increase_armor(const int armor) {
    this->target_armor += armor;
}

void Target::decrease_armor(const int armor) {
    this->target_armor -= armor;
}

int Target::get_resistance(const MagicSchool) const {
    return 70;
}

Target::CreatureType Target::get_creature_type() const {
    return this->target_type;
}

QString Target::get_creature_type_string() const {
    return creature_type_strings[target_type];
}

void Target::set_creature_type(const QString& target) {
    if (!string_to_creature_type.contains(target)) {
        qDebug() << "Creature type" << target << "not known.";
        return;
    }

    target_type = string_to_creature_type[target];
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
