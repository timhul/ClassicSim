#include "Rogue.h"

#include "Assassination.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "Combat.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "EnchantName.h"
#include "Energy.h"
#include "Equipment.h"
#include "InstantPoison.h"
#include "RaidControl.h"
#include "RelentlessStrikes.h"
#include "RogueEnchants.h"
#include "RogueSpells.h"
#include "Ruthlessness.h"
#include "SealFate.h"
#include "Stats.h"
#include "Subtlety.h"
#include "SwordSpecialization.h"
#include "Utils/Check.h"
#include "Weapon.h"

Rogue::Rogue(Race* race_, EquipmentDb* equipment_db, SimSettings* sim_settings_, RaidControl* raid_control_, const int party_, const int member) :
    Character("Rogue", "#FFF569", race_, sim_settings_, raid_control_, party_, member),
    enchant_info(new EnchantInfo()),
    combo_points(0),
    stealthed(false) {
    available_races.append("Dwarf");
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Troll");
    available_races.append("Undead");
    available_enchants = new RogueEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    // Rogue base stats
    cstats->increase_strength(60);
    cstats->increase_agility(110);
    cstats->increase_stamina(55);
    cstats->increase_intellect(15);
    cstats->increase_spirit(30);
    cstats->increase_melee_ap(100);
    cstats->increase_melee_base_crit(100);

    this->rogue_spells = new RogueSpells(this);
    this->spells = rogue_spells;
    this->energy = new class Energy(this);
    this->resource = this->energy;

    spells->activate_racials();

    this->mh_instant_poison = new InstantPoison(this, enchant_info, "MH", EnchantSlot::MAINHAND);
    this->oh_instant_poison = new InstantPoison(this, enchant_info, "OH", EnchantSlot::OFFHAND);
    this->relentless_strikes = new RelentlessStrikes(this);
    this->ruthlessness = new Ruthlessness(this);
    this->seal_fate = new SealFate(this);
    this->sword_spec = new SwordSpecialization(this);

    initialize_talents();
}

Rogue::~Rogue() {
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete mh_instant_poison;
    delete oh_instant_poison;
    delete rogue_spells;
    delete energy;
    delete relentless_strikes;
    delete ruthlessness;
    delete seal_fate;
    delete sword_spec;
    delete enchant_info;
}

double Rogue::get_agi_needed_for_one_percent_phys_crit() const {
    return 29;
}

double Rogue::get_int_needed_for_one_percent_spell_crit() const {
    return std::numeric_limits<double>::max();
}

unsigned Rogue::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Rogue::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Rogue::get_ranged_ap_per_agi() const {
    return 1;
}

double Rogue::global_cooldown() const {
    return 1.0;
}

unsigned Rogue::get_resource_level(const ResourceType) const {
    return this->energy->current;
}

unsigned Rogue::get_max_resource_level(const ResourceType) const {
    return this->energy->max;
}

void Rogue::gain_energy(const unsigned energy) {
    this->energy->gain_resource(energy);
    add_player_reaction_event();
}

void Rogue::lose_energy(const unsigned energy) {
    this->energy->lose_resource(energy);
}

unsigned Rogue::get_combo_points() const {
    return this->combo_points;
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

    spells->stop_attack();
    stealthed = true;
}

void Rogue::exit_stealth() {
    stealthed = false;
}

bool Rogue::is_stealthed() const {
    return this->stealthed;
}

Energy* Rogue::get_energy() const {
    return this->energy;
}

InstantPoison* Rogue::get_mh_instant_poison() const {
    return this->mh_instant_poison;
}

InstantPoison* Rogue::get_oh_instant_poison() const {
    return this->oh_instant_poison;
}

RelentlessStrikes* Rogue::get_relentless_strikes() const {
    return this->relentless_strikes;
}

Ruthlessness* Rogue::get_ruthlessness() const {
    return this->ruthlessness;
}

SealFate* Rogue::get_seal_fate() const {
    return this->seal_fate;
}

SwordSpecialization* Rogue::get_sword_spec() const {
    return this->sword_spec;
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
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::FIST, WeaponTypes::MACE, WeaponTypes::SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::FIST, WeaponTypes::MACE, WeaponTypes::SWORD, WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN, WeaponTypes::THROWN});
    default:
        check(false, "Rogue::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Rogue::reset_class_specific() {
    combo_points = 0;
}
