
#include "Assassination.h"
#include "Combat.h"
#include "Energy.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "Subtlety.h"
#include "Talents.h"
#include "Weapon.h"

Rogue::Rogue(Race* race, EquipmentDb *equipment_db, SimSettings *sim_settings) :
    Character(race, equipment_db, sim_settings),
    combo_points(0)
{
    available_races.append("Dwarf");
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Troll");
    available_races.append("Undead");

    this->rogue_spells = new RogueSpells(this);
    this->spells = dynamic_cast<Spells*>(rogue_spells);
    this->energy = new class Energy(this);
    this->resource = this->energy;

    spells->activate_racials();

    initialize_talents();
}

Rogue::~Rogue()
{
    delete rogue_spells;
    delete energy;
}

QString Rogue::get_name() const {
    return "Rogue";
}

QString Rogue::get_class_color() const {
    return "#FFF569";
}

int Rogue::get_strength_modifier() const {
    return 1;
}

int Rogue::get_agility_modifier() const {
    return 3;
}

int Rogue::get_stamina_modifier() const {
    return 1;
}

int Rogue::get_intellect_modifier() const {
    return 0;
}

int Rogue::get_spirit_modifier() const {
    return 0;
}

double Rogue::get_agi_needed_for_one_percent_phys_crit() const {
    return 29;
}

double Rogue::get_int_needed_for_one_percent_spell_crit() const {
    return std::numeric_limits<double>::max();
}

int Rogue::get_ap_per_strength() const {
    return 1;
}

int Rogue::get_ap_per_agi() const {
    return 1;
}

double Rogue::global_cooldown() const {
    return 1.0;
}

unsigned Rogue::get_resource_level(const ResourceType) const {
    return this->energy->current;
}

void Rogue::gain_energy(const unsigned energy) {
    this->energy->gain_resource(energy);
}

void Rogue::lose_energy(const unsigned energy) {
    this->energy->lose_resource(energy);
}

void Rogue::spend_combo_points() {
    combo_points = 0;
}

void Rogue::gain_combo_points(const unsigned combo_points) {
    this->combo_points += combo_points;

    if (this->combo_points > 5)
        this->combo_points = 5;
}

void Rogue::enter_stealth() {
    if (is_stealthed())
        return;

    stop_attack();
    stealthed = true;
}

void Rogue::exit_stealth() {
    stealthed = false;
}

bool Rogue::is_stealthed() const {
    return this->stealthed;
}

void Rogue::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new Assassination(this), new Combat(this), new Subtlety(this));
    }
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

void Rogue::reset_class_specific() {
    combo_points = 0;
}
