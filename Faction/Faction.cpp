
#include "Faction.h"

Faction::Faction() :
    current_faction(AvailableFactions::Horde),
    alliance_races({"Dwarf", "Gnome", "Human", "Night Elf"}),
    horde_races({"Orc", "Tauren", "Troll", "Undead"}),
    alliance_classes({"Druid", "Hunter", "Mage", "Paladin", "Priest", "Rogue", "Warlock", "Warrior"}),
    horde_classes({"Druid", "Hunter", "Mage", "Priest", "Shaman", "Rogue", "Warlock", "Warrior"})
{}

int Faction::get_faction() const {
    return static_cast<int>(this->current_faction);
}

AvailableFactions::Name Faction::get_faction_as_enum() const {
    return this->current_faction;
}

void Faction::switch_faction() {
    this->current_faction = is_alliance() ? AvailableFactions::Horde : AvailableFactions::Alliance;
}

const QVector<QString>& Faction::get_faction_races() const {
    return is_horde() ? horde_races : alliance_races;
}

const QVector<QString>& Faction::get_faction_classes() const {
    return is_horde() ? horde_classes : alliance_classes;
}

bool Faction::is_alliance() const {
    return this->current_faction == AvailableFactions::Alliance;
}

bool Faction::is_horde() const {
    return this->current_faction == AvailableFactions::Horde;
}
