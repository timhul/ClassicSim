#include "Faction.h"

#include "Race.h"
#include "Utils/Check.h"

Faction::Faction(Race* race) :
    alliance_races({"Dwarf", "Gnome", "Human", "Night Elf"}),
    horde_races({"Orc", "Tauren", "Troll", "Undead"}),
    alliance_classes({"Druid", "Hunter", "Mage", "Paladin", "Priest", "Rogue", "Warlock", "Warrior"}),
    horde_classes({"Druid", "Hunter", "Mage", "Priest", "Shaman", "Rogue", "Warlock", "Warrior"})
{
    current_faction = alliance_races.contains(race->get_name()) ? AvailableFactions::Alliance :
                                                                  AvailableFactions::Horde;

    check((alliance_races.contains(race->get_name()) || horde_races.contains(race->get_name())),
          QString("Race '%1' missing faction").arg(race->get_name()).toStdString());
}

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

bool Faction::is_alliance() const {
    return this->current_faction == AvailableFactions::Alliance;
}

bool Faction::is_horde() const {
    return this->current_faction == AvailableFactions::Horde;
}
