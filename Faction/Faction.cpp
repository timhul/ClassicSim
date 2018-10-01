
#include "Faction.h"

Faction::Faction() :
    faction(true),
    alliance_races({"Dwarf", "Gnome", "Human", "Night Elf"}),
    horde_races({"Orc", "Tauren", "Troll", "Undead"}),
    alliance_classes({"Druid", "Hunter", "Mage", "Paladin", "Priest", "Rogue", "Warlock", "Warrior"}),
    horde_classes({"Druid", "Hunter", "Mage", "Priest", "Shaman", "Rogue", "Warlock", "Warrior"})
{}

bool Faction::get_faction() const {
    return this->faction;
}

void Faction::switch_faction() {
    this->faction = !this->faction;
}

const QVector<QString>& Faction::get_faction_races() const {
    return this->faction ? horde_races : alliance_races;
}

const QVector<QString>& Faction::get_faction_classes() const {
    return this->faction ? horde_classes : alliance_classes;
}

bool Faction::is_alliance() const {
    return !this->faction;
}

bool Faction::is_horde() const {
    return !is_alliance();
}
