
#include "Paladin.h"
#include "PaladinSpells.h"
#include "PaladinStatistics.h"
#include "Weapon.h"

Paladin::Paladin(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, Faction* faction, QObject *parent) :
    Character(race, engine, _eq, _roll, faction, parent) {
    available_races.append("Dwarf");
    available_races.append("Human");
    this->statistics = new PaladinStatistics();

    this->paladin_spells = new PaladinSpells(this);
    this->spells = dynamic_cast<Spells*>(paladin_spells);
}

Paladin::~Paladin()
{
    delete paladin_spells;
    delete statistics;
}

QString Paladin::get_name() const {
    return "Paladin";
}

QString Paladin::get_class_color() const {
    return "#F58CBA";
}

int Paladin::get_strength_modifier() const {
    return 2;
}

int Paladin::get_agility_modifier() const {
    return 0;
}

int Paladin::get_stamina_modifier() const {
    return 2;
}

int Paladin::get_intellect_modifier() const {
    return 0;
}

int Paladin::get_spirit_modifier() const {
    return 1;
}

int Paladin::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Paladin::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Paladin::get_ap_per_strength() const {
    return 1;
}

int Paladin::get_ap_per_agi() const {
    return 1;
}

double Paladin::global_cooldown() const {
    return 1.5;
}

void Paladin::initialize_talents() {

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
        assert(false);
        return QVector<int>();
    }
}
