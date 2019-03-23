#include "Mage.h"

#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "MageSpells.h"
#include "Mana.h"
#include "Utils/Check.h"
#include "Weapon.h"

Mage::Mage(Race* race, EquipmentDb* equipment_db, SimSettings *sim_settings) :
    Character("Mage", race, sim_settings) {
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Troll");
    available_races.append("Undead");

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    cstats->increase_agility(35);
    cstats->increase_strength(25);
    cstats->increase_stamina(45);
    cstats->increase_intellect(125);
    cstats->increase_spirit(120);

    this->mage_spells = new MageSpells(this);
    this->spells = dynamic_cast<CharacterSpells*>(mage_spells);

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1273);
}

Mage::~Mage()
{
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete cstats;
    delete mage_spells;
    delete mana;
}

QString Mage::get_class_color() const {
    return "#69CCF0";
}

unsigned Mage::get_strength_modifier() const {
    return 0;
}

unsigned Mage::get_agility_modifier() const {
    return 0;
}

unsigned Mage::get_stamina_modifier() const {
    return 0;
}

unsigned Mage::get_intellect_modifier() const {
    return 3;
}

unsigned Mage::get_spirit_modifier() const {
    return 2;
}

unsigned Mage::get_mp5_from_spirit() const {
    return 13 + static_cast<unsigned>(round(cstats->get_spirit() / 4));
}

double Mage::get_agi_needed_for_one_percent_phys_crit() const {
    return std::numeric_limits<double>::max();
}

double Mage::get_int_needed_for_one_percent_spell_crit() const {
    return 59.5;
}

unsigned Mage::get_ap_per_strength() const {
    return 1;
}

unsigned Mage::get_ap_per_agi() const {
    return 1;
}

double Mage::global_cooldown() const {
    return 1.5;
}

void Mage::initialize_talents() {

}

unsigned Mage::get_resource_level(const ResourceType) const {
    return mana->current;
}

int Mage::get_highest_possible_armor_type() const {
    return ArmorTypes::CLOTH;
}

QVector<int> Mage::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::SWORD, WeaponTypes::STAFF});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::WAND});
    default:
        check(false, "Reached end of switch");
        return QVector<int>();
    }
}

void Mage::reset_class_specific() {

}
