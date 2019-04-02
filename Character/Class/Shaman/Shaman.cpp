#include "Shaman.h"

#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "Mana.h"
#include "ShamanSpells.h"
#include "Utils/Check.h"
#include "Weapon.h"

Shaman::Shaman(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings) :
    Character("Shaman", race, sim_settings) {
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    cstats->increase_agility(30);
    cstats->increase_strength(70);
    cstats->increase_stamina(75);
    cstats->increase_intellect(65);
    cstats->increase_spirit(80);

    this->shaman_spells = new ShamanSpells(this);
    this->spells = dynamic_cast<CharacterSpells*>(shaman_spells);

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1520);
}

Shaman::~Shaman()
{
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete shaman_spells;
    delete mana;
}

QString Shaman::get_class_color() const {
    return "#0070DE";
}

unsigned Shaman::get_strength_modifier() const {
    return 1;
}

unsigned Shaman::get_agility_modifier() const {
    return 0;
}

unsigned Shaman::get_stamina_modifier() const {
    return 1;
}

unsigned Shaman::get_intellect_modifier() const {
    return 1;
}

unsigned Shaman::get_spirit_modifier() const {
    return 2;
}

double Shaman::get_mp5_from_spirit() const {
    return 15 + static_cast<double>(cstats->get_spirit()) / 5;
}

double Shaman::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Shaman::get_int_needed_for_one_percent_spell_crit() const {
    return 59.5;
}

unsigned Shaman::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Shaman::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Shaman::get_ranged_ap_per_agi() const {
    return 0;
}

double Shaman::global_cooldown() const {
    return 1.5;
}

void Shaman::initialize_talents() {

}

unsigned Shaman::get_resource_level(const ResourceType) const {
    return mana->current;
}

int Shaman::get_highest_possible_armor_type() const {
    return ArmorTypes::MAIL;
}

QVector<int> Shaman::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::POLEARM,
                             WeaponTypes::STAFF, WeaponTypes::TWOHAND_AXE,
                             WeaponTypes::TWOHAND_MACE});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND, WeaponTypes::SHIELD});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::TOTEM});
    default:
        check(false, "Shaman::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Shaman::reset_class_specific() {

}
