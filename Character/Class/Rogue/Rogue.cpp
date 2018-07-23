
#include "Rogue.h"
#include "RogueSpells.h"
#include "RogueStatistics.h"
#include "Weapon.h"

Rogue::Rogue(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, Faction* faction, QObject *parent) :
    Character(race, engine, _eq, _roll, faction, parent) {
    available_races.append("Dwarf");
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Troll");
    available_races.append("Undead");
    this->statistics = new RogueStatistics();

    this->rogue_spells = new RogueSpells(this);
    this->spells = dynamic_cast<Spells*>(rogue_spells);

    apply_racial_effects();
}

Rogue::~Rogue()
{
    delete rogue_spells;
    delete statistics;
}

QString Rogue::get_name(void) const {
    return "Rogue";
}

QString Rogue::get_class_color() const {
    return "#FFF569";
}

int Rogue::get_strength_modifier(void) const {
    return 1;
}

int Rogue::get_agility_modifier(void) const {
    return 3;
}

int Rogue::get_stamina_modifier(void) const {
    return 1;
}

int Rogue::get_intellect_modifier(void) const {
    return 0;
}

int Rogue::get_spirit_modifier(void) const {
    return 0;
}

int Rogue::get_agi_needed_for_one_percent_phys_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Rogue::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
}

int Rogue::get_ap_per_strength() const {
    return 1;
}

int Rogue::get_ap_per_agi() const {
    return 1;
}

float Rogue::global_cooldown() const {
    return 1.0;
}

void Rogue::initialize_talents() {

}

int Rogue::get_highest_possible_armor_type() const {
    return ArmorTypes::LEATHER;
}

QVector<int> Rogue::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::FIST,
                            WeaponTypes::MACE, WeaponTypes::SWORD, WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN,
                            WeaponTypes::THROWN});
    default:
        assert(false);
        return QVector<int>();
    }
}
