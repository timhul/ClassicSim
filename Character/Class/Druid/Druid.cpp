
#include "Druid.h"
#include "DruidSpells.h"
#include "DruidStatistics.h"
#include "Race.h"
#include "Weapon.h"

Druid::Druid(Race* race, EquipmentDb *equipment_db, SimSettings *sim_settings) :
    Character(race, equipment_db, sim_settings) {
    available_races.append("Night Elf");
    available_races.append("Tauren");
    this->statistics = new DruidStatistics(sim_settings);

    this->druid_spells = new DruidSpells(this);
    this->spells = dynamic_cast<Spells*>(druid_spells);
}

Druid::~Druid()
{
    delete druid_spells;
    delete statistics;
}

QString Druid::get_name() const {
    return "Druid";
}

QString Druid::get_class_color() const {
    return "#FF7D0A";
}

int Druid::get_strength_modifier() const {
    return 1;
}

int Druid::get_agility_modifier() const {
    return 0;
}

int Druid::get_stamina_modifier() const {
    return 0;
}

int Druid::get_intellect_modifier() const {
    return 2;
}

int Druid::get_spirit_modifier() const {
    return 2;
}

double Druid::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Druid::get_int_needed_for_one_percent_spell_crit() const {
    return 60.0;
}

int Druid::get_ap_per_strength() const {
    return 1;
}

int Druid::get_ap_per_agi() const {
    return 1;
}

double Druid::global_cooldown() const {
    // Incomplete implementation, is stance specific.
    return 1.5;
}

void Druid::initialize_talents() {

}

int Druid::get_highest_possible_armor_type() const {
    return ArmorTypes::LEATHER;
}

QVector<int> Druid::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::POLEARM,
                             WeaponTypes::STAFF});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::IDOL});
    default:
        assert(false);
        return QVector<int>();
    }
}

void Druid::reset_spells() {

}
