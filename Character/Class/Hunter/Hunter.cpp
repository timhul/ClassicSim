#include "Hunter.h"

#include "BeastMastery.h"
#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "HunterEnchants.h"
#include "HunterSpells.h"
#include "Mana.h"
#include "Marksmanship.h"
#include "Survival.h"
#include "Talents.h"
#include "Utils/Check.h"
#include "Weapon.h"

Hunter::Hunter(Race* race, EquipmentDb *equipment_db, SimSettings *sim_settings) :
    Character("Hunter", race, sim_settings) {
    available_races.append("Dwarf");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");
    available_enchants = new HunterEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    cstats->increase_agility(100);
    cstats->increase_strength(35);
    cstats->increase_stamina(70);
    cstats->increase_intellect(45);
    cstats->increase_spirit(50);
    cstats->increase_ranged_crit(300);
    cstats->increase_ranged_ap(160);

    this->hunter_spells = new HunterSpells(this);
    this->spells = dynamic_cast<CharacterSpells*>(hunter_spells);

    this->mana = new class Mana(this);
    this->resource = this->mana;
    mana->set_base_mana(1720);

    initialize_talents();
}

Hunter::~Hunter()
{
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete hunter_spells;
    delete mana;
}

QString Hunter::get_class_color() const {
    return "#ABD473";
}

unsigned Hunter::get_strength_modifier() const {
    return 0;
}

unsigned Hunter::get_agility_modifier() const {
    return 3;
}

unsigned Hunter::get_stamina_modifier() const {
    return 1;
}

unsigned Hunter::get_intellect_modifier() const {
    return 0;
}

unsigned Hunter::get_spirit_modifier() const {
    return 1;
}

unsigned Hunter::get_mp5_from_spirit() const {
    return 15 + static_cast<unsigned>(round(cstats->get_spirit() / 5));
}

double Hunter::get_agi_needed_for_one_percent_phys_crit() const {
    return 53.0;
}

double Hunter::get_int_needed_for_one_percent_spell_crit() const {
    return std::numeric_limits<double>::max();
}

unsigned Hunter::get_ap_per_strength() const {
    return 1;
}

unsigned Hunter::get_ap_per_agi() const {
    return 1;
}

double Hunter::global_cooldown() const {
    return 1.5;
}

void Hunter::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new BeastMastery(this), new Marksmanship(this), new Survival(this));
    }
}

unsigned Hunter::get_resource_level(const ResourceType) const {
    return mana->current;
}

void Hunter::gain_mana(const unsigned value) {
    mana->gain_resource(value);
}

void Hunter::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

int Hunter::get_highest_possible_armor_type() const {
    return ArmorTypes::MAIL;
}

QVector<int> Hunter::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::SWORD, WeaponTypes::POLEARM, WeaponTypes::STAFF,
                             WeaponTypes::TWOHAND_AXE, WeaponTypes::TWOHAND_SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN});
    default:
        check(false, "Reached end of switch");
        return QVector<int>();
    }
}

void Hunter::reset_class_specific() {

}
