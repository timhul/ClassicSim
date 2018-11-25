#include "Shaman.h"

#include "CharacterStats.h"
#include "Mana.h"
#include "ShamanSpells.h"
#include "Weapon.h"

Shaman::Shaman(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings) :
    Character(race, sim_settings) {
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");

    this->cstats = new CharacterStats(this, equipment_db);

    this->shaman_spells = new ShamanSpells(this);
    this->spells = dynamic_cast<Spells*>(shaman_spells);

    this->mana = new class Mana(this);
    this->resource = this->mana;
}

Shaman::~Shaman()
{
    delete shaman_spells;
    delete mana;
}

QString Shaman::get_name() const {
    return "Shaman";
}

QString Shaman::get_class_color() const {
    return "#0070DE";
}

int Shaman::get_strength_modifier() const {
    return 1;
}

int Shaman::get_agility_modifier() const {
    return 0;
}

int Shaman::get_stamina_modifier() const {
    return 1;
}

int Shaman::get_intellect_modifier() const {
    return 1;
}

int Shaman::get_spirit_modifier() const {
    return 2;
}

double Shaman::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Shaman::get_int_needed_for_one_percent_spell_crit() const {
    return 59.5;
}

int Shaman::get_ap_per_strength() const {
    return 1;
}

int Shaman::get_ap_per_agi() const {
    return 1;
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
        assert(false);
        return QVector<int>();
    }
}

void Shaman::reset_class_specific() {

}
