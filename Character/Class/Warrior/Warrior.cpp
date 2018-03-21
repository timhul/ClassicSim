
#include "Warrior.h"
#include "PlayerAction.h"
#include "Bloodthirst.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "Flurry.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include <QDebug>

Warrior::Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll) :
    Character(race, engine, _eq) {
    // Constants added as a hack, these are the gains from 1-60.
    // This essentially forces a clvl of 60 for stats to be accurate for warrior.
    this->STR += get_strength_modifier() + 97;
    this->AGI += get_agility_modifier() + 60;
    this->STAM += get_stamina_modifier() + 88;
    this->INT += get_intellect_modifier() + 10;
    this->SPI += get_spirit_modifier() + 25;
    this->rage = 0;
    this->roll = _roll;
    this->bt = new Bloodthirst(engine, dynamic_cast<Character*>(this), roll);
    this->mh_attack = new MainhandAttack(engine, dynamic_cast<Character*>(this), roll);
    this->oh_attack = new OffhandAttack(engine, dynamic_cast<Character*>(this), roll);
    this->flurry = new Flurry(dynamic_cast<Character*>(this));
}

Warrior::~Warrior() {
    delete bt;
    delete mh_attack;
    delete oh_attack;
}

QString Warrior::get_name(void) const {
    return "Warrior";
}

int Warrior::get_strength_modifier(void) const {
    return 3;
}

int Warrior::get_agility_modifier(void) const {
    return 0;
}

int Warrior::get_stamina_modifier(void) const {
    return 2;
}

int Warrior::get_intellect_modifier(void) const {
    return 0;
}

int Warrior::get_spirit_modifier(void) const {
    return 0;
}

int Warrior::get_melee_ap(void) {
    // TODO: Include AP from buffs (Crusader, Might Rage Potion, world buffs, etc.)
    return get_strength() * 2;
}

void Warrior::gain_rage(const int gained_rage) {
    assert(gained_rage >= 0);
    this->rage += gained_rage;

    // TODO: Add statistics for rage lost due to overcapping.
    if (this->rage > 100)
        rage = 100;
}

void Warrior::lose_rage(const int lost_rage) {
    assert(lost_rage > 0);
    this->rage -= lost_rage;
    assert(this->rage >= 0);
}

int Warrior::rage_gained_from_dd(const int damage_dealt) const {
    // Using the 307 damage dealt = 10 rage formula.
    // TODO: add max(1, round(damage_dealt/30.7))
    return int(ceil(damage_dealt/30.7));
}

void Warrior::rotation() {
    // TODO: Some classes will need "special gcd" for stances, totems, shapeshifts, auras(?), etc.
    // Fury warriors need this for overpower modelling.

    if (!is_melee_attacking())
        start_attack();

    if (!action_ready()) {
        return;
    }

    // TODO: Check if execute is available. Requires target health.

    if (bt->is_available(rage))
        lose_rage(bt->perform(rage));
}

void Warrior::add_next_mh_attack(void) {
    MainhandMeleeHit* new_event = new MainhandMeleeHit(this, mh_attack->get_next_expected_use(), mh_attack->get_next_iteration());
    this->get_engine()->add_event(new_event);
}

void Warrior::add_next_oh_attack(void) {
    OffhandMeleeHit* new_event = new OffhandMeleeHit(this, oh_attack->get_next_expected_use(), oh_attack->get_next_iteration());
    this->get_engine()->add_event(new_event);
}

void Warrior::mh_auto_attack(const int iteration) {
    if (!mh_attack->attack_is_valid(iteration))
        return;
    // TODO: Check if Heroic Strike "buff" up
    // Then do not perform mh_attack.

    gain_rage(mh_attack->perform(rage));

    if (action_ready()) {
        PlayerAction* new_event = new PlayerAction(this, 0.1);
        this->get_engine()->add_event(new_event);
    }

    mh_attack->update_next_expected_use(0.0);
    add_next_mh_attack();
}

void Warrior::oh_auto_attack(const int iteration) {
    if (!oh_attack->attack_is_valid(iteration))
        return;

    gain_rage(oh_attack->perform(rage));

    if (action_ready()) {
        PlayerAction* new_event = new PlayerAction(this, 0.1);
        this->get_engine()->add_event(new_event);
    }

    oh_attack->update_next_expected_use(0.0);
    add_next_oh_attack();
}

float Warrior::global_cooldown() const {
    return 1.5;
}

int Warrior::get_curr_rage() const {
    return this->rage;
}

Flurry* Warrior::get_flurry() const {
    return this->flurry;
}

void Warrior::increase_hit(float increase) {
    percent_hit += increase;
}

void Warrior::increase_crit(float increase) {
    percent_crit += increase;
}

void Warrior::increase_attack_speed(float increase) {
    qDebug() << engine->get_current_priority() << ": Attack speed increased by " << increase * 100 << "%";
    percent_attack_speed += increase;

    mh_attack->update_next_expected_use(increase);
    add_next_mh_attack();

    if (equipment->is_dual_wielding()) {
        oh_attack->update_next_expected_use(increase);
        add_next_oh_attack();
    }
}

void Warrior::decrease_hit(float decrease) {
    percent_hit -= decrease;
}

void Warrior::decrease_crit(float decrease) {
    percent_crit -= decrease;
}

void Warrior::decrease_attack_speed(float decrease) {
    qDebug() << engine->get_current_priority() << ": Attack speed decreased by " << decrease * 100 << "%";
    percent_attack_speed -= decrease;

    mh_attack->update_next_expected_use(decrease);
    add_next_mh_attack();

    if (equipment->is_dual_wielding()) {
        oh_attack->update_next_expected_use(decrease);
        add_next_oh_attack();
    }
}
