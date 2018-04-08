
#include "Character.h"
#include "Race.h"
#include "Engine.h"
#include "Equipment.h"
#include "Mechanics.h"
#include "Talents.h"
#include "Stats.h"
#include "Buff.h"

#include <QDebug>

Character::Character(Race* race, Engine* engine, Equipment* equipment, QObject* parent) :
    QObject(parent)
{
    this->race = race;
    this->engine = engine;
    this->equipment = equipment;
    this->talents = new Talents();
    this->stats = new Stats(this);
    this->clvl = 1;
    this->melee_attacking = false;
    this->last_action = 0 - this->global_cooldown();
    // TODO: Get haste enchants from gear
    // TODO: Find out swing timer without weapons equipped.
    mh_wpn_speed = has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() :
                                    2.0;
    oh_wpn_speed = has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() :
                                   300.0;
    // TODO: Populate this->buffs with general buffs.
}

Character::~Character() {
    delete talents;
    delete stats;
}

Race* Character::get_race(void) {
    return this->race;
}

int Character::get_strength(void) {
    return stats->get_strength();
}

int Character::get_agility(void) {
    return stats->get_agility();
}

int Character::get_stamina(void) {
    return stats->get_stamina();
}

int Character::get_intellect(void) {
    return stats->get_intellect();
}

int Character::get_spirit(void) {
    return stats->get_spirit();
}

float Character::get_hit_chance(void) const {
    return stats->get_hit_chance();
}

float Character::get_crit_chance(void) const {
    return stats->get_crit_chance();
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

void Character::add_next_mh_attack(void) {
    return;
}

void Character::add_next_oh_attack(void) {
    return;
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

float Character::global_cooldown() const {
    return 1.5;
}

bool Character::action_ready() const {
    // Allow some rounding errors (this could effectively speed up gcd by 1/10000ths of a second).
    float delta = last_action + global_cooldown() - engine->get_current_priority();
    return delta < 0.0001;
}

int Character::get_melee_ap() {
    return stats->get_melee_ap_total();
}

int Character::get_mh_dmg() {
    // TODO: Check if base weapon speed should be used, or hasted.
    MeleeWeapon* mh = equipment->get_mainhand();
    float normalized_dmg = mh->get_random_dmg() / mh->get_base_weapon_speed();
    float normalized_ap = get_melee_ap() / 14;

    return (normalized_dmg + normalized_ap) * mh->get_base_weapon_speed();
}

int Character::get_oh_dmg() {
    // TODO: Check if base weapon speed should be used, or hasted.
    MeleeWeapon* oh = equipment->get_offhand();
    float normalized_dmg = oh->get_random_dmg() / oh->get_base_weapon_speed();
    float normalized_ap = get_melee_ap() / 14;

    return (normalized_dmg + normalized_ap) * oh->get_base_weapon_speed();
}

int Character::get_mh_wpn_skill() {
    int racial_bonus = 0;
    switch (equipment->get_mainhand()->get_weapon_type()) {
    case WeaponTypes::AXE:
        racial_bonus += race->get_axe_bonus();
        break;
    case WeaponTypes::SWORD:
        racial_bonus += race->get_sword_bonus();
        break;
    case WeaponTypes::MACE:
        racial_bonus += race->get_mace_bonus();
        break;
    }
    return get_clvl() * 5 + racial_bonus;
}

int Character::get_oh_wpn_skill() {
    int racial_bonus = 0;
    switch (equipment->get_offhand()->get_weapon_type()) {
    case WeaponTypes::AXE:
        racial_bonus += race->get_axe_bonus();
        break;
    case WeaponTypes::SWORD:
        racial_bonus += race->get_sword_bonus();
        break;
    case WeaponTypes::MACE:
        racial_bonus += race->get_mace_bonus();
        break;
    }
    return get_clvl() * 5 + racial_bonus;
}

void Character::increase_hit(float increase) {
    percent_hit += increase;
    stats->increase_hit(increase);
}

void Character::decrease_hit(float decrease) {
    percent_hit -= decrease;
    stats->decrease_hit(decrease);
}

void Character::increase_crit(float increase) {
    percent_crit += increase;
    stats->increase_crit(increase);
}

void Character::decrease_crit(float decrease) {
    percent_crit -= decrease;
    stats->decrease_crit(decrease);
}

void Character::increase_attack_speed(int increase) {
    attack_speed_buffs.append(increase);

    mh_wpn_speed /= 1 + float(increase / 100);

    if (has_offhand())
        oh_wpn_speed /= 1 + float(increase / 100);
}

void Character::decrease_attack_speed(int decrease) {
    assert(attack_speed_buffs.removeOne(decrease));

    mh_wpn_speed /= 1 - float(decrease / 100);

    if (has_offhand())
        oh_wpn_speed /= 1 - float(decrease / 100);
}

float Character::get_mh_wpn_speed() {
    return mh_wpn_speed;
}

float Character::get_oh_wpn_speed() {
    return oh_wpn_speed;
}

float Character::get_avg_mh_damage() {
    if (!has_mainhand())
        return 1;

    return (equipment->get_mainhand()->get_min_dmg() + equipment->get_mainhand()->get_max_dmg()) / 2;
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

    reset_spells();

    assert(attack_speed_buffs.empty());
}
