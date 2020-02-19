#include "Mage.h"

#include "Arcane.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "Combustion.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "Fire.h"
#include "Frost.h"
#include "Gnome.h"
#include "Human.h"
#include "MageEnchants.h"
#include "MageSpells.h"
#include "Mana.h"
#include "RaidControl.h"
#include "Utils/Check.h"
#include "Weapon.h"

Mage::Mage(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings, RaidControl* raid_control, const int party, const int member) :
    Character("Mage", "#69CCF0", race, sim_settings, raid_control, party, member) {
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Troll");
    available_races.append("Undead");
    available_enchants = new MageEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    // Mage base stats
    cstats->increase_strength(10);
    cstats->increase_agility(15);
    cstats->increase_stamina(25);
    cstats->increase_intellect(105);
    cstats->increase_spirit(100);

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1273);

    this->mage_spells = new MageSpells(this);
    this->spells = mage_spells;

    mage_spells->activate_racials();

    initialize_talents();
}

Mage::~Mage() {
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete mage_spells;
    delete mana;
}

double Mage::get_mp5_from_spirit() const {
    return 13 + static_cast<double>(cstats->get_spirit()) / 4;
}

double Mage::get_agi_needed_for_one_percent_phys_crit() const {
    return std::numeric_limits<double>::max();
}

double Mage::get_int_needed_for_one_percent_spell_crit() const {
    return 59.5;
}

unsigned Mage::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Mage::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Mage::get_ranged_ap_per_agi() const {
    return 0;
}

double Mage::global_cooldown() const {
    return 1.5;
}

void Mage::initialize_talents() {
    for (int i = 0; i < 3; ++i)
        talents->add_talent_tree(new Arcane(this), new Fire(this), new Frost(this));
}

unsigned Mage::get_resource_level(const ResourceType) const {
    return mana->current;
}

unsigned Mage::get_max_resource_level(const ResourceType) const {
    return mana->max;
}

void Mage::gain_mana(const unsigned value) {
    mana->gain_resource(value);
    add_player_reaction_event();
}

void Mage::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

void Mage::increase_base_mana(const unsigned value) {
    mana->base_mana += value;
}

void Mage::decrease_base_mana(const unsigned value) {
    mana->base_mana -= value;
}

void Mage::spell_hit_effect(MagicSchool magic_school) {
    switch (magic_school) {
    case MagicSchool::Fire:
        mage_spells->get_combustion()->stack_crit_chance();
        break;
    default:
        break;
    }

    enabled_procs->run_proc_check(ProcInfo::Source::MagicSpell);
}

void Mage::spell_critical_effect(MagicSchool magic_school) {
    switch (magic_school) {
    case MagicSchool::Fire:
        mage_spells->get_combustion()->use_charge();
        break;
    default:
        break;
    }

    enabled_procs->run_proc_check(ProcInfo::Source::MagicSpell);
}

void Mage::increase_mp5_within_5sr_modifier(const double increase) {
    mana->mp5_from_spirit_within_5sr_modifier += increase;
}

void Mage::decrease_mp5_within_5sr_modifier(const double decrease) {
    mana->mp5_from_spirit_within_5sr_modifier -= decrease;
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
        check(false, "Mage::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Mage::reset_class_specific() {}
