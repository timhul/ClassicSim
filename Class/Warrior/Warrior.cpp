#include "Warrior.h"

#include "Arms.h"
#include "Buff.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "CombatRoll.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Engine.h"
#include "Equipment.h"
#include "Fury.h"
#include "PlayerAction.h"
#include "Protection.h"
#include "Race.h"
#include "Rage.h"
#include "RaidControl.h"
#include "Stats.h"
#include "Utils/Check.h"
#include "WarriorEnchants.h"
#include "WarriorSpells.h"
#include "Weapon.h"

Warrior::Warrior(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings, RaidControl* raid_control, const int party, const int member) :
    Character("Warrior", "#C79C6E", race, sim_settings, raid_control, party, member) {
    available_races.append("Dwarf");
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");
    available_races.append("Undead");
    this->available_enchants = new WarriorEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    cstats->increase_agility(60);
    cstats->increase_intellect(10);
    cstats->increase_spirit(25);
    cstats->increase_stamina(90);
    cstats->increase_strength(100);
    cstats->increase_melee_ap(160);

    this->rage = new class Rage();
    this->resource = this->rage;
    this->stance = WarriorStances::Battle;
    this->stance_rage_remainder = 0;
    this->next_stance_cd = 0.0;

    this->warr_spells = new WarriorSpells(this);
    this->spells = warr_spells;

    initialize_talents();

    spells->activate_racials();
}

Warrior::~Warrior() {
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete warr_spells;
    delete rage;
}

unsigned Warrior::get_strength_modifier() const {
    return 3;
}

unsigned Warrior::get_agility_modifier() const {
    return 0;
}

unsigned Warrior::get_stamina_modifier() const {
    return 2;
}

unsigned Warrior::get_intellect_modifier() const {
    return 0;
}

unsigned Warrior::get_spirit_modifier() const {
    return 0;
}

double Warrior::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Warrior::get_int_needed_for_one_percent_spell_crit() const {
    return std::numeric_limits<double>::max();
}

unsigned Warrior::get_melee_ap_per_strength() const {
    return 2;
}

unsigned Warrior::get_melee_ap_per_agi() const {
    return 0;
}

unsigned Warrior::get_ranged_ap_per_agi() const {
    return 0;
}

void Warrior::gain_rage(const unsigned gained_rage) {
    this->rage->gain_resource(gained_rage);
    add_player_reaction_event();
}

void Warrior::lose_rage(const unsigned lost_rage) {
    this->rage->lose_resource(lost_rage);
}

unsigned Warrior::rage_gained_from_dd(const unsigned damage_dealt) const {
    return static_cast<unsigned>(std::max(1, int(round(damage_dealt / rage_conversion_value * 7.5))));
}

void Warrior::set_clvl(const unsigned clvl) {
    this->clvl = clvl;
    this->rage_conversion_value = 0.0091107836 * std::pow(clvl, 2) + 3.225598133 * clvl + 4.2652911;
}

int Warrior::get_highest_possible_armor_type() const {
    return ArmorTypes::PLATE;
}

QVector<int> Warrior::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::SWORD, WeaponTypes::POLEARM,
                             WeaponTypes::STAFF, WeaponTypes::TWOHAND_AXE,
                             WeaponTypes::TWOHAND_MACE, WeaponTypes::TWOHAND_SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::SWORD, WeaponTypes::CASTER_OFFHAND,
                             WeaponTypes::SHIELD});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN,
                             WeaponTypes::THROWN});
    default:
        check(false, "Warrior::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

double Warrior::global_cooldown() const {
    return 1.5;
}

double Warrior::stance_cooldown() const {
    return 1.0;
}

unsigned Warrior::get_resource_level(const ResourceType) const {
    return this->rage->current;
}

unsigned Warrior::get_max_resource_level(const ResourceType) const {
    return this->rage->max;
}

void Warrior::increase_stance_rage_remainder() {
    this->stance_rage_remainder += 5;
    check((stance_rage_remainder <= 25), "Stance rage remainder too high");
}

void Warrior::decrease_stance_rage_remainder() {
    check((stance_rage_remainder >= 5), "Underflow Warrior:decrease_stance_rage_remainder()");
    this->stance_rage_remainder -= 5;
}

unsigned Warrior::get_stance_remainder() const {
    return this->stance_rage_remainder;
}

bool Warrior::on_stance_cooldown() const {
    return engine->get_current_priority() < this->next_stance_cd;
}

void Warrior::new_stance_effect() {
    switch (this->stance) {
    case WarriorStances::Berserker:
        warr_spells->get_berserker_stance_buff()->apply_buff();
        break;
    case WarriorStances::Defensive:
        warr_spells->get_defensive_stance_buff()->apply_buff();
        break;
    }

    if (this->rage->current > stance_rage_remainder)
        this->rage->current = stance_rage_remainder;

    if ((engine->get_current_priority() + 0.5) > this->next_gcd) {
        this->next_gcd = engine->get_current_priority() + 0.5;
        engine->add_event(new PlayerAction(spells, next_gcd));
    }

    this->next_stance_cd = engine->get_current_priority() + stance_cooldown();
}

void Warrior::switch_to_battle_stance() {
    switch (this->stance) {
    case WarriorStances::Berserker:
        warr_spells->get_berserker_stance_buff()->cancel_buff();
        break;
    case WarriorStances::Defensive:
        warr_spells->get_defensive_stance_buff()->cancel_buff();
        break;
    }

    this->stance = WarriorStances::Battle;
    new_stance_effect();
}

void Warrior::switch_to_berserker_stance() {
    switch (this->stance) {
    case WarriorStances::Defensive:
        warr_spells->get_defensive_stance_buff()->cancel_buff();
        break;
    }

    this->stance = WarriorStances::Berserker;
    new_stance_effect();
}

void Warrior::switch_to_defensive_stance() {
    switch (this->stance) {
    case WarriorStances::Berserker:
        warr_spells->get_berserker_stance_buff()->cancel_buff();
        break;
    }

    this->stance = WarriorStances::Defensive;
    new_stance_effect();
}

bool Warrior::in_battle_stance() const {
    return this->stance == WarriorStances::Battle;
}

bool Warrior::in_berserker_stance() const {
    return this->stance == WarriorStances::Berserker;
}

bool Warrior::in_defensive_stance() const {
    return this->stance == WarriorStances::Defensive;
}

void Warrior::melee_mh_white_critical_effect() {
    warr_spells->get_flurry()->apply_buff();
    warr_spells->apply_deep_wounds();

    enabled_procs->run_proc_check(ProcInfo::Source::MainhandSwing);
}

void Warrior::melee_mh_yellow_critical_effect() {
    warr_spells->get_flurry()->apply_buff();
    warr_spells->apply_deep_wounds();

    enabled_procs->run_proc_check(ProcInfo::Source::MainhandSpell);
}

void Warrior::melee_oh_white_critical_effect() {
    warr_spells->get_flurry()->apply_buff();
    warr_spells->apply_deep_wounds();

    enabled_procs->run_proc_check(ProcInfo::Source::OffhandSwing);
}

void Warrior::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new Arms(this), new Fury(this), new Protection(this));
    }
}

void Warrior::reset_class_specific() {
    this->next_stance_cd = 0.0 - stance_cooldown();
}
