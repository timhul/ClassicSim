
#include "Character.h"
#include "Race.h"
#include "Engine.h"
#include "Equipment.h"
#include "Faction.h"
#include "Talents.h"
#include "CharacterStats.h"
#include "Stats.h"
#include "ActiveProcs.h"
#include "ProcInfo.h"
#include "ActiveBuffs.h"
#include "Spells.h"
#include "CombatRoll.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "Weapon.h"
#include <QDebug>

Character::Character(Race* race, Engine* engine, Equipment* equipment, CombatRoll* roll, Faction* faction, QObject* parent) :
    QObject(parent)
{
    this->race = race;
    this->engine = engine;
    this->roll = roll;
    this->faction = faction,
    this->talents = new Talents();
    // TODO: Consider saving equipment pointer as well, to shorten expressions.
    equipment->set_character(this);
    this->cstats = new CharacterStats(this, equipment);
    this->active_procs = new ActiveProcs(this, faction);
    this->active_buffs = new ActiveBuffs(this, faction);
    this->statistics = nullptr;
    this->clvl = 1;
    this->melee_attacking = false;
    this->last_action = 0 - this->global_cooldown();
    this->ability_crit_dmg_mod = 2.0;
}

Character::~Character() {
    delete talents;
    delete cstats;
    delete active_procs;
    delete active_buffs;
}

Race* Character::get_race(void) {
    return this->race;
}

bool Character::race_available(Race* race) const {
    return available_races.contains(race->get_name());
}

void Character::set_race(Race* race) {
    assert(race_available(race));

    this->race = race;
}

void Character::switch_faction() {
    // TODO: When all classes have implemented ClassStatistics remove this.
    if (this->statistics == nullptr)
        return;

    active_procs->switch_faction();
    active_buffs->switch_faction();
}

void Character::rotation() {
    spells->rotation();
}

int Character::get_clvl(void) const {
    return this->clvl;
}

void Character::set_clvl(const int& clvl) {
    this->clvl = clvl;
}

bool Character::is_dual_wielding(void) {
    return cstats->get_equipment()->is_dual_wielding();
}

bool Character::is_melee_attacking(void) const {
    return melee_attacking;
}

Engine* Character::get_engine(void) const {
    return this->engine;
}

CombatRoll* Character::get_combat_roll(void) const {
    return this->roll;
}

Equipment* Character::get_equipment(void) const {
    return this->cstats->get_equipment();
}

Talents* Character::get_talents(void) const {
    return this->talents;
}

ActiveBuffs* Character::get_active_buffs(void) const {
    return this->active_buffs;
}

Spells* Character::get_spells(void) const {
    return this->spells;
}

CharacterStats* Character::get_stats(void) const {
    return this->cstats;
}

ClassStatistics* Character::get_statistics(void) const {
    return this->statistics;
}

ActiveProcs* Character::get_active_procs() const {
    return this->active_procs;
}

void Character::start_attack(void) {
    this->melee_attacking = true;

    spells->start_attack();
}

void Character::stop_attack(void) {
    this->melee_attacking = false;
}

void Character::start_global_cooldown() {
    assert(action_ready());
    this->last_action = engine->get_current_priority();
}

float Character::global_cooldown() const {
    return 1.5;
}

bool Character::action_ready() const {
    // Allow some rounding errors (this could effectively speed up gcd by 1/10000ths of a second).
    float delta = last_action + global_cooldown() - engine->get_current_priority();
    return delta < 0.0001;
}

void Character::melee_mh_white_hit_effect() {
    run_mh_white_specific_proc_effects();
}

void Character::melee_mh_yellow_hit_effect() {
    run_mh_yellow_specific_proc_effects();
}

void Character::melee_mh_white_critical_effect() {
    run_mh_white_specific_proc_effects();
}

void Character::melee_mh_yellow_critical_effect() {
    run_mh_yellow_specific_proc_effects();
}

void Character::melee_oh_white_hit_effect() {
    run_oh_white_specific_proc_effects();
}

void Character::melee_oh_yellow_hit_effect() {
    run_oh_yellow_specific_proc_effects();
}

void Character::melee_oh_white_critical_effect() {
    run_oh_white_specific_proc_effects();
}

void Character::melee_oh_yellow_critical_effect() {
    run_oh_yellow_specific_proc_effects();
}


void Character::spell_hit_effect() {

}

void Character::spell_critical_effect() {

}

void Character::run_mh_white_specific_proc_effects() {
    active_procs->run_proc_effects(ProcInfo::Source::MainhandSwing);
}

void Character::run_mh_yellow_specific_proc_effects() {
    active_procs->run_proc_effects(ProcInfo::Source::MainhandSpell);
}

void Character::run_oh_white_specific_proc_effects() {
    active_procs->run_proc_effects(ProcInfo::Source::OffhandSwing);
}

void Character::run_oh_yellow_specific_proc_effects() {
    active_procs->run_proc_effects(ProcInfo::Source::OffhandSpell);
}

void Character::run_extra_mh_attack() {
    spells->get_mh_attack()->extra_attack();
}

void Character::run_extra_oh_attack() {
    spells->get_oh_attack()->extra_attack();
}

float Character::get_ability_crit_dmg_mod() const {
    return ability_crit_dmg_mod;
}

float Character::get_total_phys_dmg_mod() const {
    return cstats->get_total_phys_dmg_mod();
}

float Character::get_random_normalized_mh_dmg() {
    Weapon* mh = cstats->get_equipment()->get_mainhand();
    return get_normalized_dmg(mh->get_random_dmg(), mh);
}

float Character::get_random_non_normalized_mh_dmg() {
    Weapon* mh = cstats->get_equipment()->get_mainhand();
    return get_non_normalized_dmg(mh->get_random_dmg(), mh->get_base_weapon_speed());
}

float Character::get_random_normalized_oh_dmg() {
    Weapon* oh = cstats->get_equipment()->get_offhand();
    return get_normalized_dmg(oh->get_random_dmg(), oh);
}

float Character::get_random_non_normalized_oh_dmg() {
    Weapon* oh = cstats->get_equipment()->get_offhand();
    return get_non_normalized_dmg(oh->get_random_dmg(), oh->get_base_weapon_speed());
}

int Character::get_avg_mh_damage() {
    if (!has_mainhand())
        return get_normalized_dmg(1, nullptr);

    Weapon* mh = cstats->get_equipment()->get_mainhand();
    int avg_dmg = int(round(mh->get_min_dmg() + mh->get_max_dmg()) / 2);
    return get_non_normalized_dmg(avg_dmg, mh->get_base_weapon_speed());
}

float Character::get_normalized_dmg(const int damage, const Weapon* weapon) {
    // TODO: Consider moving these types of mechanical assumptions into e.g. Mechanics
    if (weapon == nullptr)
        return get_non_normalized_dmg(damage, 2.0);

    float normalized_wpn_speed = -1;

    switch (weapon->get_weapon_slot()) {
    case WeaponSlots::MAINHAND:
    case WeaponSlots::OFFHAND:
    case WeaponSlots::ONEHAND:
        normalized_wpn_speed = weapon->get_weapon_type() == WeaponTypes::DAGGER ? 1.7 : 2.4;
        break;
    case WeaponSlots::TWOHAND:
        normalized_wpn_speed = 3.3;
        break;
    case WeaponSlots::RANGED:
        normalized_wpn_speed = 2.8;
        break;
    default:
        assert(false);
    }

    return get_non_normalized_dmg(damage, normalized_wpn_speed);
}

float Character::get_non_normalized_dmg(const int damage, const float wpn_speed) {
    return damage + (wpn_speed * cstats->get_melee_ap() / 14);
}

int Character::get_mh_wpn_skill() {
    return cstats->get_equipment()->get_mainhand() != nullptr ? get_wpn_skill(cstats->get_equipment()->get_mainhand()) :
                                                                get_clvl() * 5;
}

int Character::get_oh_wpn_skill() {
    return cstats->get_equipment()->get_offhand() != nullptr ? get_wpn_skill(cstats->get_equipment()->get_offhand()) :
                                                               get_clvl() * 5;
}

int Character::get_wpn_skill(Weapon* weapon) const {
    int skill_bonus = 0;
    switch (weapon->get_weapon_type()) {
    case WeaponTypes::AXE:
        skill_bonus += race->get_axe_bonus() + cstats->get_equipment()->get_stats()->get_axe_skill();
        break;
    case WeaponTypes::DAGGER:
        skill_bonus += cstats->get_equipment()->get_stats()->get_dagger_skill();
        break;
    case WeaponTypes::SWORD:
        skill_bonus += race->get_sword_bonus() + cstats->get_equipment()->get_stats()->get_sword_skill();
        break;
    case WeaponTypes::MACE:
        skill_bonus += race->get_mace_bonus() + cstats->get_equipment()->get_stats()->get_mace_skill();
        break;
    }
    return get_clvl() * 5 + skill_bonus;
}

void Character::increase_attack_speed(int increase) {
    cstats->increase_haste(increase);
    float increase_float = float(increase) / 100;

    spells->get_mh_attack()->update_next_expected_use(increase_float);
    // TODO: Check if actually attacking
    spells->add_next_mh_attack();

    if (cstats->get_equipment()->is_dual_wielding()) {
        spells->get_oh_attack()->update_next_expected_use(increase_float);
        // TODO: Check if actually attacking
        spells->add_next_oh_attack();
    }
}

void Character::decrease_attack_speed(int decrease) {
    cstats->decrease_haste(decrease);
    float decrease_float = float(decrease) / 100;

    spells->get_mh_attack()->update_next_expected_use(-decrease_float);
    // TODO: Check if actually attacking
    spells->add_next_mh_attack();

    if (cstats->get_equipment()->is_dual_wielding()) {
        spells->get_oh_attack()->update_next_expected_use(-decrease_float);
        // TODO: Check if actually attacking
        spells->add_next_oh_attack();
    }
}

void Character::increase_ability_crit_dmg_mod(float increase) {
    ability_crit_dmg_mod += increase;
}

void Character::decrease_ability_crit_dmg_mod(float decrease) {
    ability_crit_dmg_mod -= decrease;
}

bool Character::has_mainhand() const {
    return cstats->get_equipment()->get_mainhand() != nullptr;
}

bool Character::has_offhand() const {
    return cstats->get_equipment()->get_offhand() != nullptr;
}

void Character::reset() {
    melee_attacking = false;
    last_action = 0 - this->global_cooldown();

    active_buffs->reset();
    reset_spells();
    active_procs->reset();
    cstats->reset();

    reset_resource();
}

void Character::dump() {
    qDebug() << "--------------------------------------";
    qDebug() << get_name();
    qDebug() << "STRENGTH" << cstats->get_strength();
    qDebug() << "AGILITY" << cstats->get_agility();
    qDebug() << "STAMINA" << cstats->get_stamina();
    qDebug() << "INTELLECT" << cstats->get_intellect();
    qDebug() << "SPIRIT" << cstats->get_spirit();
    qDebug() << "MH Wpn skill" << get_mh_wpn_skill();
    qDebug() << "OH Wpn skill" << get_oh_wpn_skill();
    qDebug() << "MH DPS" << (cstats->get_equipment()->get_mainhand() != nullptr ? QString::number(cstats->get_equipment()->get_mainhand()->get_wpn_dps()) : "No MH");
    qDebug() << "OH DPS" << (cstats->get_equipment()->get_offhand() != nullptr ? QString::number(cstats->get_equipment()->get_offhand()->get_wpn_dps()) : "No OH");
    qDebug() << "Hit chance" << cstats->get_hit_chance();
    qDebug() << "Crit chance" << cstats->get_crit_chance();
    qDebug() << "--------------------------------------";
}
