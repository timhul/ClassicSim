#include "Paladin.h"

#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "HolyPaladin.h"
#include "Mana.h"
#include "PaladinEnchants.h"
#include "PaladinSpells.h"
#include "ProtectionPaladin.h"
#include "RaidControl.h"
#include "Retribution.h"
#include "Utils/Check.h"
#include "Vengeance.h"
#include "Weapon.h"

Paladin::Paladin(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings, RaidControl* raid_control, const int party, const int member) :
    Character("Paladin", "#F58CBA", race, sim_settings, raid_control, party, member) {
    available_races.append("Dwarf");
    available_races.append("Human");
    available_enchants = new PaladinEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    cstats->increase_agility(20);
    cstats->increase_strength(15);
    cstats->increase_stamina(30);
    cstats->increase_intellect(100);
    cstats->increase_spirit(105);
    cstats->increase_melee_crit(300);
    cstats->increase_melee_ap(160);

    this->paladin_spells = new PaladinSpells(this);
    this->spells = dynamic_cast<CharacterSpells*>(paladin_spells);

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1436);

    this->vengeance = new Vengeance(this);

    initialize_talents();
}

Paladin::~Paladin()
{
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete paladin_spells;
    delete mana;
    delete vengeance;
}

unsigned Paladin::get_strength_modifier() const {
    return 2;
}

unsigned Paladin::get_agility_modifier() const {
    return 0;
}

unsigned Paladin::get_stamina_modifier() const {
    return 2;
}

unsigned Paladin::get_intellect_modifier() const {
    return 0;
}

unsigned Paladin::get_spirit_modifier() const {
    return 1;
}

double Paladin::get_mp5_from_spirit() const {
    return 15 + static_cast<double>(cstats->get_spirit()) / 5;
}

double Paladin::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Paladin::get_int_needed_for_one_percent_spell_crit() const {
    return 54;
}

unsigned Paladin::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Paladin::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Paladin::get_ranged_ap_per_agi() const {
    return 0;
}

double Paladin::global_cooldown() const {
    return 1.5;
}

void Paladin::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new HolyPaladin(this), new ProtectionPaladin(this), new Retribution(this));
    }
}

unsigned Paladin::get_resource_level(const ResourceType) const {
    return mana->current;
}

unsigned Paladin::get_max_resource_level(const ResourceType) const {
    return mana->max;
}

void Paladin::gain_mana(const unsigned value) {
    mana->gain_resource(value);
    add_player_reaction_event();
}

void Paladin::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

void Paladin::increase_base_mana(const unsigned value) {
    mana->base_mana += value;
}

void Paladin::decrease_base_mana(const unsigned value) {
    mana->base_mana -= value;
}

Buff* Paladin::get_vengeance() const {
    return this->vengeance;
}

int Paladin::get_highest_possible_armor_type() const {
    return ArmorTypes::PLATE;
}

QVector<int> Paladin::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::MACE, WeaponTypes::SWORD,
                             WeaponTypes::POLEARM, WeaponTypes::TWOHAND_AXE,
                             WeaponTypes::TWOHAND_MACE, WeaponTypes::TWOHAND_SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND, WeaponTypes::SHIELD});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::LIBRAM});
    default:
        check(false, "Paladin::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Paladin::reset_class_specific() {

}
