
#include "Mage.h"
#include "MageSpells.h"
#include "MageStatistics.h"
#include "Weapon.h"

Mage::Mage(Race* race, EquipmentDb* equipment_db, QObject *parent) :
    Character(race, equipment_db, parent) {
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Troll");
    available_races.append("Undead");
    this->statistics = new MageStatistics();

    this->mage_spells = new MageSpells(this);
    this->spells = dynamic_cast<Spells*>(mage_spells);
}

Mage::~Mage()
{
    delete mage_spells;
    delete statistics;
}

QString Mage::get_name() const {
    return "Mage";
}

QString Mage::get_class_color() const {
    return "#69CCF0";
}

int Mage::get_strength_modifier() const {
    return 0;
}

int Mage::get_agility_modifier() const {
    return 0;
}

int Mage::get_stamina_modifier() const {
    return 0;
}

int Mage::get_intellect_modifier() const {
    return 3;
}

int Mage::get_spirit_modifier() const {
    return 2;
}

int Mage::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Mage::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Mage::get_ap_per_strength() const {
    return 1;
}

int Mage::get_ap_per_agi() const {
    return 1;
}

double Mage::global_cooldown() const {
    return 1.5;
}

void Mage::initialize_talents() {

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
        assert(false);
        return QVector<int>();
    }
}
