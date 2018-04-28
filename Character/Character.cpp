
#include "Character.h"
#include "Race.h"
#include "Engine.h"
#include "Equipment.h"
#include "Mechanics.h"
#include "Talents.h"
#include "Stats.h"
#include "Buff.h"
#include "Spell.h"
#include "CombatRoll.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"

#include <QDebug>

Character::Character(Race* race, Engine* engine, Equipment* equipment, CombatRoll* roll, QObject* parent) :
    QObject(parent)
{
    this->race = race;
    this->engine = engine;
    this->equipment = equipment;
    this->roll = roll;
    this->talents = new Talents();
    this->base_stats = new Stats();
    this->clvl = 1;
    this->melee_attacking = false;
    this->last_action = 0 - this->global_cooldown();
    this->ability_crit_dmg_mod = 2.0;
    this->total_phys_dmg_mod = 1.0;
    // TODO: Get haste enchants from gear
    this->mh_haste = 0;
    this->oh_haste = 0;
    // TODO: Populate this->buffs with general buffs.
}

Character::~Character() {
    delete talents;
    delete base_stats;

    for (int i = 0; i < spells.size(); ++i) {
        delete spells[i];
    }

    for (int i = 0; i < buffs.size(); ++i) {
        delete buffs[i];
    }

    spells.clear();
    buffs.clear();
}

Race* Character::get_race(void) {
    return this->race;
}

int Character::get_strength(void) {
    return base_stats->get_strength() + equipment->get_stats()->get_strength();
}

int Character::get_agility(void) {
    return base_stats->get_agility() + equipment->get_stats()->get_agility();
}

int Character::get_stamina(void) {
    return base_stats->get_stamina() + equipment->get_stats()->get_stamina();
}

int Character::get_intellect(void) {
    return base_stats->get_intellect() + equipment->get_stats()->get_intellect();
}

int Character::get_spirit(void) {
    return base_stats->get_spirit() + equipment->get_stats()->get_spirit();
}

float Character::get_hit_chance(void) const {
    return base_stats->get_hit_chance()  + equipment->get_stats()->get_hit_chance();
}

float Character::get_crit_chance(void) const {
    return base_stats->get_crit_chance()  + equipment->get_stats()->get_crit_chance();
}

int Character::get_clvl(void) const {
    return this->clvl;
}

void Character::set_clvl(const int& clvl) {
    this->clvl = clvl;
}

bool Character::is_dual_wielding(void) {
    return equipment->is_dual_wielding();
}

bool Character::is_melee_attacking(void) const {
    return melee_attacking;
}

Engine* Character::get_engine(void) const {
    return this->engine;
}

Equipment* Character::get_equipment(void) const {
    return this->equipment;
}

Talents* Character::get_talents(void) const {
    return this->talents;
}

MainhandAttack* Character::get_mh_attack() const {
    return this->mh_attack;
}

OffhandAttack* Character::get_oh_attack() const {
    return this->oh_attack;
}


void Character::add_next_mh_attack(void) {
    MainhandMeleeHit* new_event = new MainhandMeleeHit(this, mh_attack->get_next_expected_use(), mh_attack->get_next_iteration());
    this->get_engine()->add_event(new_event);
}

void Character::add_next_oh_attack(void) {
    OffhandMeleeHit* new_event = new OffhandMeleeHit(this, oh_attack->get_next_expected_use(), oh_attack->get_next_iteration());
    this->get_engine()->add_event(new_event);
}

void Character::start_attack(void) {
    this->melee_attacking = true;

    add_next_mh_attack();

    if (is_dual_wielding()) {
        add_next_oh_attack();
    }
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

int Character::get_melee_ap() {
    return base_stats->get_melee_ap_total()  + equipment->get_stats()->get_melee_ap_total();
}

void Character::increase_melee_ap(const int increase) {
    base_stats->increase_base_melee_ap(increase);
}

void Character::decrease_melee_ap(const int decrease) {
    base_stats->decrease_base_melee_ap(decrease);
}

void Character::melee_critical_effect() {

}

float Character::get_ability_crit_dmg_mod() const {
    return ability_crit_dmg_mod;
}

float Character::get_total_phys_dmg_mod() const {
    // TODO: Include e.g. Two-Handed Weapon Specialization if using 2-handers.
    return total_phys_dmg_mod;
}

float Character::get_random_normalized_mh_dmg() {
    Weapon* mh = equipment->get_mainhand();
    return get_normalized_dmg(mh->get_random_dmg(), mh);
}

float Character::get_random_non_normalized_mh_dmg() {
    Weapon* mh = equipment->get_mainhand();
    return get_non_normalized_dmg(mh->get_random_dmg(), mh->get_base_weapon_speed());
}

float Character::get_random_normalized_oh_dmg() {
    Weapon* oh = equipment->get_offhand();
    return get_normalized_dmg(oh->get_random_dmg(), oh);
}

float Character::get_random_non_normalized_oh_dmg() {
    Weapon* oh = equipment->get_offhand();
    return get_non_normalized_dmg(oh->get_random_dmg(), oh->get_base_weapon_speed());
}

int Character::get_avg_mh_damage() {
    if (!has_mainhand())
        return 1;

    Weapon* mh = equipment->get_mainhand();
    int avg_dmg = int(round(mh->get_min_dmg() + mh->get_max_dmg()) / 2);
    return get_non_normalized_dmg(avg_dmg, mh->get_base_weapon_speed());
}

float Character::get_normalized_dmg(const int damage, const Weapon* weapon) {
    // TODO: Consider moving these types of mechanical assumptions into e.g. Mechanics
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
    return damage + (wpn_speed * get_melee_ap() / 14);
}

int Character::get_mh_wpn_skill() {
    return equipment->get_mainhand() != nullptr ? get_wpn_skill(equipment->get_mainhand()) :
                                                  get_clvl() * 5;
}

int Character::get_oh_wpn_skill() {
    return equipment->get_offhand() != nullptr ? get_wpn_skill(equipment->get_offhand()) :
                                                 get_clvl() * 5;
}

int Character::get_wpn_skill(Weapon* weapon) const {
    int skill_bonus = 0;
    switch (weapon->get_weapon_type()) {
    case WeaponTypes::AXE:
        skill_bonus += race->get_axe_bonus() + equipment->get_stats()->get_axe_skill();
        break;
    case WeaponTypes::DAGGER:
        skill_bonus += equipment->get_stats()->get_dagger_skill();
        break;
    case WeaponTypes::SWORD:
        skill_bonus += race->get_sword_bonus() + equipment->get_stats()->get_sword_skill();
        break;
    case WeaponTypes::MACE:
        skill_bonus += race->get_mace_bonus() + equipment->get_stats()->get_mace_skill();
        break;
    }
    return get_clvl() * 5 + skill_bonus;
}

void Character::increase_hit(float increase) {
    base_stats->increase_hit(increase);
}

void Character::decrease_hit(float decrease) {
    base_stats->decrease_hit(decrease);
}

void Character::increase_crit(float increase) {
    base_stats->increase_crit(increase);
    roll->update_crit_chance(base_stats->get_crit_chance());
}

void Character::decrease_crit(float decrease) {
    base_stats->decrease_crit(decrease);
    roll->update_crit_chance(base_stats->get_crit_chance());
}

void Character::increase_attack_speed(int increase) {
    attack_speed_buffs.append(increase);
    float increase_float = float(increase) / 100;
    mh_haste += increase_float;

    if (has_offhand())
        oh_haste += increase_float;

    base_stats->increase_attack_speed(increase_float);

    mh_attack->update_next_expected_use(increase_float);
    add_next_mh_attack();

    if (equipment->is_dual_wielding()) {
        oh_attack->update_next_expected_use(increase_float);
        add_next_oh_attack();
    }
}

void Character::decrease_attack_speed(int decrease) {
    assert(attack_speed_buffs.removeOne(decrease));
    float decrease_float = float(decrease) / 100;
    mh_haste -= decrease_float;

    if (has_offhand())
        oh_haste -= decrease_float;

    base_stats->decrease_attack_speed(decrease_float);

    mh_attack->update_next_expected_use(-decrease_float);
    add_next_mh_attack();

    if (equipment->is_dual_wielding()) {
        oh_attack->update_next_expected_use(-decrease_float);
        add_next_oh_attack();
    }
}

void Character::increase_ability_crit_dmg_mod(float increase) {
    ability_crit_dmg_mod += increase;
}

void Character::decrease_ability_crit_dmg_mod(float decrease) {
    ability_crit_dmg_mod -= decrease;
}

void Character::increase_total_phys_dmg_mod(float increase) {
    total_phys_dmg_mod += increase;
}

void Character::decrease_total_phys_dmg_mod(float decrease) {
    total_phys_dmg_mod -= decrease;
}

float Character::get_mh_wpn_speed() {
    return has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / (1 + mh_haste) :
            2.0 / 1 + mh_haste;
}

float Character::get_oh_wpn_speed() {
    return has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / (1 + oh_haste) :
            300;
}

bool Character::has_mainhand() const {
    return equipment->get_mainhand() != nullptr;
}

bool Character::has_offhand() const {
    return equipment->get_offhand() != nullptr;
}

void Character::reset() {
    melee_attacking = false;
    last_action = 0 - this->global_cooldown();

    for (int i = 0; i < buffs.size(); ++i) {
        buffs[i]->reset();
    }

    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }

    reset_resource();

    assert(attack_speed_buffs.empty());
}

void Character::dump() {
    qDebug() << "--------------------------------------";
    qDebug() << get_name();
    qDebug() << "STRENGTH" << get_strength();
    qDebug() << "AGILITY" << get_agility();
    qDebug() << "STAMINA" << get_stamina();
    qDebug() << "INTELLECT" << get_intellect();
    qDebug() << "SPIRIT" << get_spirit();
    qDebug() << "MH Wpn skill" << get_mh_wpn_skill();
    qDebug() << "OH Wpn skill" << get_oh_wpn_skill();
    qDebug() << "MH DPS" << (equipment->get_mainhand() != nullptr ? QString::number(equipment->get_mainhand()->get_wpn_dps()) : "No MH");
    qDebug() << "OH DPS" << (equipment->get_offhand() != nullptr ? QString::number(equipment->get_offhand()->get_wpn_dps()) : "No OH");
    qDebug() << "Hit chance" << get_hit_chance();
    qDebug() << "Crit chance" << get_crit_chance();
    qDebug() << "--------------------------------------";
}
