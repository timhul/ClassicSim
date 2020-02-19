#include "Warlock.h"

#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "Mana.h"
#include "RaidControl.h"
#include "Utils/Check.h"
#include "WarlockSpells.h"
#include "Weapon.h"

Warlock::Warlock(Race* race_, EquipmentDb* equipment_db, SimSettings* sim_settings_, RaidControl* raid_control_, const int party_, const int member) :
    Character("Warlock", "#9482C9", race_, sim_settings_, raid_control_, party_, member) {
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Orc");
    available_races.append("Undead");

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    // Warlock base stats
    cstats->increase_agility(30);
    cstats->increase_strength(25);
    cstats->increase_stamina(45);
    cstats->increase_intellect(90);
    cstats->increase_spirit(95);

    this->warlock_spells = new WarlockSpells(this);
    this->spells = warlock_spells;

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1373);

    warlock_spells->activate_racials();
}

Warlock::~Warlock() {
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete cstats;
    delete warlock_spells;
    delete mana;
}

double Warlock::get_mp5_from_spirit() const {
    return 8 + static_cast<double>(cstats->get_spirit()) / 4;
}

double Warlock::get_agi_needed_for_one_percent_phys_crit() const {
    return std::numeric_limits<double>::max();
}

double Warlock::get_int_needed_for_one_percent_spell_crit() const {
    return 60.6;
}

unsigned Warlock::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Warlock::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Warlock::get_ranged_ap_per_agi() const {
    return 0;
}

double Warlock::global_cooldown() const {
    return 1.5;
}

void Warlock::initialize_talents() {}

unsigned Warlock::get_resource_level(const ResourceType) const {
    return mana->current;
}

unsigned Warlock::get_max_resource_level(const ResourceType) const {
    return mana->max;
}

void Warlock::gain_mana(const unsigned value) {
    mana->gain_resource(value);
    add_player_reaction_event();
}

void Warlock::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

void Warlock::increase_base_mana(const unsigned value) {
    mana->base_mana += value;
}

void Warlock::decrease_base_mana(const unsigned value) {
    mana->base_mana -= value;
}

int Warlock::get_highest_possible_armor_type() const {
    return ArmorTypes::CLOTH;
}

QVector<int> Warlock::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::SWORD, WeaponTypes::STAFF});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::WAND});
    default:
        check(false, "Warlock::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Warlock::reset_class_specific() {}
