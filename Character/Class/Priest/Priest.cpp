
#include "Priest.h"
#include "PriestSpells.h"
#include "Weapon.h"

Priest::Priest(Race* race, EquipmentDb* equipment_db, SimSettings *sim_settings) :
    Character(race, equipment_db, sim_settings) {
    available_races.append("Dwarf");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Troll");
    available_races.append("Undead");

    this->priest_spells = new PriestSpells(this);
    this->spells = dynamic_cast<Spells*>(priest_spells);
}

Priest::~Priest()
{
    delete priest_spells;
}

QString Priest::get_name() const {
    return "Priest";
}

QString Priest::get_class_color() const {
    return "#FFFFFF";
}

int Priest::get_strength_modifier() const {
    return 0;
}

int Priest::get_agility_modifier() const {
    return 0;
}

int Priest::get_stamina_modifier() const {
    return 0;
}

int Priest::get_intellect_modifier() const {
    return 2;
}

int Priest::get_spirit_modifier() const {
    return 3;
}

double Priest::get_agi_needed_for_one_percent_phys_crit() const {
    return std::numeric_limits<double>::max();
}

double Priest::get_int_needed_for_one_percent_spell_crit() const {
    return 59.2;
}

int Priest::get_ap_per_strength() const {
    return 1;
}

int Priest::get_ap_per_agi() const {
    return 1;
}

double Priest::global_cooldown() const {
    return 1.5;
}

void Priest::initialize_talents() {

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
        assert(false);
        return QVector<int>();
    }
}

void Priest::reset_class_specific() {

}
