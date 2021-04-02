#include "Priest.h"

#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "Discipline.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "Holy.h"
#include "Mana.h"
#include "RaidControl.h"
#include "Shadow.h"
#include "Utils/Check.h"
#include "PriestEnchants.h"
#include "PriestSpells.h"
#include "Weapon.h"

Priest::Priest(Race* race_, EquipmentDb* equipment_db, SimSettings* sim_settings_, RaidControl* raid_control_, const int party_, const int member) :
    Character("Priest", "#FFFFFF", race_, sim_settings_, raid_control_, party_, member) {
    available_races.append("Dwarf");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Troll");
    available_races.append("Undead");
    available_enchants = new PriestEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    // Priest base stats
    cstats->increase_strength(15);
    cstats->increase_agility(20);
    cstats->increase_stamina(30);
    cstats->increase_intellect(100);
    cstats->increase_spirit(105);

    this->priest_spells = new PriestSpells(this);
    this->spells = priest_spells;

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1436);

    priest_spells->activate_racials();

    initialize_talents();
}

Priest::~Priest() {
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete priest_spells;
    delete mana;
}

double Priest::get_mp5_from_spirit() const {
    return 13 + static_cast<double>(cstats->get_spirit()) / 4;
}

double Priest::get_agi_needed_for_one_percent_phys_crit() const {
    return std::numeric_limits<double>::max();
}

double Priest::get_int_needed_for_one_percent_spell_crit() const {
    return 59.2;
}

unsigned Priest::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Priest::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Priest::get_ranged_ap_per_agi() const {
    return 0;
}

double Priest::global_cooldown() const {
    return 1.5;
}

void Priest::initialize_talents() {
        for (int i = 0; i < 3; ++i)
            talents->add_talent_tree(new Discipline(this), new Holy(this), new Shadow(this));
}

unsigned Priest::get_resource_level(const ResourceType) const {
    return mana->current;
}

unsigned Priest::get_max_resource_level(const ResourceType) const {
    return mana->max;
}

void Priest::gain_mana(const unsigned value) {
    mana->gain_resource(value);
    add_player_reaction_event();
}

void Priest::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

void Priest::increase_base_mana(const unsigned value) {
    mana->base_mana += value;
}

void Priest::decrease_base_mana(const unsigned value) {
    mana->base_mana -= value;
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
        check(false, "Priest::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Priest::reset_class_specific() {}
