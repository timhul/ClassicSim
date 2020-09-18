#include "Hunter.h"

#include "BeastMastery.h"
#include "Cat.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "HunterEnchants.h"
#include "HunterSpells.h"
#include "Mana.h"
#include "Marksmanship.h"
#include "RaidControl.h"
#include "Survival.h"
#include "Utils/Check.h"
#include "Weapon.h"

Hunter::Hunter(Race* race_, EquipmentDb* equipment_db, SimSettings* sim_settings_, RaidControl* raid_control_, const int party_, const int member) :
    Character("Hunter", "#ABD473", race_, sim_settings_, raid_control_, party_, member), projectile_dps(0.0) {
    available_races.append("Dwarf");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");
    available_enchants = new HunterEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    // Hunter base stats
    cstats->increase_strength(35);
    cstats->increase_agility(105);
    cstats->increase_stamina(70);
    cstats->increase_intellect(45);
    cstats->increase_spirit(50);
    cstats->increase_ranged_ap(100);

    this->hunter_spells = new HunterSpells(this);
    this->spells = hunter_spells;

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1720);

    this->pet = new Cat(this);

    initialize_talents();

    hunter_spells->activate_racials();
}

Hunter::~Hunter() {
    cstats->get_equipment()->unequip_all();

    enabled_buffs->clear_all();
    enabled_procs->clear_all();
    delete pet;

    delete available_enchants;
    delete cstats;
    delete hunter_spells;
    delete mana;
}

double Hunter::get_mp5_from_spirit() const {
    return 15 + static_cast<double>(cstats->get_spirit()) / 5;
}

double Hunter::get_agi_needed_for_one_percent_phys_crit() const {
    return 52.5;
}

double Hunter::get_int_needed_for_one_percent_spell_crit() const {
    return std::numeric_limits<double>::max();
}

unsigned Hunter::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Hunter::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Hunter::get_ranged_ap_per_agi() const {
    return 2;
}

double Hunter::global_cooldown() const {
    return 1.5;
}

void Hunter::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new BeastMastery(this), new Marksmanship(this), new Survival(this));
    }
}

unsigned Hunter::get_resource_level(const ResourceType resource_type) const {
    switch (resource_type) {
    case ResourceType::Mana:
        return mana->current;
    case ResourceType::Focus:
        return pet->get_resource_level();
    default:
        return 0;
    }
}

unsigned Hunter::get_max_resource_level(const ResourceType resource_type) const {
    switch (resource_type) {
    case ResourceType::Mana:
        return mana->max;
    case ResourceType::Focus:
        check(false, QString("%1 Focus not available for max resource level").arg(__func__).toStdString());
    default:
        return 0;
    }
}

void Hunter::gain_mana(const unsigned value) {
    mana->gain_resource(value);
    add_player_reaction_event();
}

void Hunter::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

void Hunter::gain_focus(const unsigned value) {
    pet->get_resource()->gain_resource(value);
    pet->add_pet_reaction();
}

void Hunter::increase_base_mana(const unsigned value) {
    mana->base_mana += value;
}

void Hunter::decrease_base_mana(const unsigned value) {
    mana->base_mana -= value;
}

double Hunter::get_non_normalized_projectile_dmg_bonus() const {
    return this->projectile_dps * cstats->get_ranged_wpn_speed();
}

double Hunter::get_normalized_projectile_dmg_bonus() const {
    return this->projectile_dps * 2.8;
}

void Hunter::set_projectile_dps(const double dps) {
    this->projectile_dps = dps;
}

int Hunter::get_highest_possible_armor_type() const {
    return ArmorTypes::MAIL;
}

QVector<int> Hunter::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST, WeaponTypes::SWORD, WeaponTypes::POLEARM, WeaponTypes::STAFF,
                             WeaponTypes::TWOHAND_AXE, WeaponTypes::TWOHAND_SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({
            WeaponTypes::AXE,
            WeaponTypes::DAGGER,
            WeaponTypes::FIST,
            WeaponTypes::SWORD,
        });
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN});
    default:
        check(false, "Hunter::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Hunter::reset_class_specific() {
    pet->reset();
}
