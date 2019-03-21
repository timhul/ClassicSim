#include "Priest.h"

#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "Mana.h"
#include "PriestSpells.h"
#include "Utils/Check.h"
#include "Weapon.h"

Priest::Priest(Race* race, EquipmentDb* equipment_db, SimSettings *sim_settings) :
    Character("Priest", race, sim_settings) {
    available_races.append("Dwarf");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Troll");
    available_races.append("Undead");

    this->cstats = new CharacterStats(this, equipment_db);

    this->priest_spells = new PriestSpells(this);
    this->spells = dynamic_cast<CharacterSpells*>(priest_spells);

    this->mana = new class Mana(this);
    this->resource = this->mana;
}

Priest::~Priest()
{
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete cstats;
    delete priest_spells;
    delete mana;
}

QString Priest::get_class_color() const {
    return "#FFFFFF";
}

unsigned Priest::get_strength_modifier() const {
    return 0;
}

unsigned Priest::get_agility_modifier() const {
    return 0;
}

unsigned Priest::get_stamina_modifier() const {
    return 0;
}

unsigned Priest::get_intellect_modifier() const {
    return 2;
}

unsigned Priest::get_spirit_modifier() const {
    return 3;
}

double Priest::get_agi_needed_for_one_percent_phys_crit() const {
    return std::numeric_limits<double>::max();
}

double Priest::get_int_needed_for_one_percent_spell_crit() const {
    return 59.2;
}

unsigned Priest::get_ap_per_strength() const {
    return 1;
}

unsigned Priest::get_ap_per_agi() const {
    return 1;
}

double Priest::global_cooldown() const {
    return 1.5;
}

void Priest::initialize_talents() {

}

unsigned Priest::get_resource_level(const ResourceType) const {
    return mana->current;
}

int Priest::get_highest_possible_armor_type() const {
    return ArmorTypes::CLOTH;
}

QVector<int> Priest::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::MACE, WeaponTypes::STAFF});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::WAND});
    default:
        check(false, "Reached end of switch");
        return QVector<int>();
    }
}

void Priest::reset_class_specific() {

}
