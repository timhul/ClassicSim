
#include "WarriorSpells.h"
#include "Warrior.h"

#include "PlayerAction.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"

#include "BattleShout.h"
#include "BerserkerRage.h"
#include "Bloodrage.h"
#include "Bloodthirst.h"
#include "DeathWish.h"
#include "DeepWounds.h"
#include "Execute.h"
#include "HeroicStrike.h"
#include "Overpower.h"
#include "Whirlwind.h"

#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"

#include "Flurry.h"
#include "HeroicStrikeBuff.h"
#include "UnbridledWrath.h"
#include "DeathWishBuff.h"
#include "BattleShoutBuff.h"

WarriorSpells::WarriorSpells(Warrior* pchar) :
    Spells(pchar),
    pchar(pchar)
{
    this->bt = new Bloodthirst(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->deep_wounds = new DeepWounds(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->heroic_strike = new HeroicStrike(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->execute = new Execute(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->overpower = new Overpower(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->death_wish = new DeathWish(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->battle_shout = new BattleShout(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->berserker_rage = new BerserkerRage(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->bloodrage = new Bloodrage(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->whirlwind = new Whirlwind(pchar->get_engine(), pchar, pchar->get_combat_roll());

    this->mh_attack = new MainhandAttackWarrior(pchar->get_engine(), pchar, pchar->get_combat_roll());
    this->oh_attack = new OffhandAttackWarrior(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spells.append(bt);
    spells.append(deep_wounds);
    spells.append(heroic_strike);
    spells.append(execute);
    spells.append(overpower);
    spells.append(death_wish);
    spells.append(battle_shout);
    spells.append(berserker_rage);
    spells.append(bloodrage);
    spells.append(whirlwind);
    spells.append(mh_attack);
    spells.append(oh_attack);
}

WarriorSpells::~WarriorSpells()
{}

void WarriorSpells::reset() {
    for (int i = 0; i < spells.size(); ++i) {
        spells[i]->reset();
    }
}

void WarriorSpells::rotation() {
    // TODO: Some classes will need "special gcd" for stances, totems, shapeshifts, auras(?), etc.
    // Fury warriors need this for overpower modelling.
    if (!pchar->is_melee_attacking()) {
        pchar->start_attack();
    }

    if (pchar->get_curr_rage() < 50)
        try_berserker_rage();

    if (pchar->get_curr_rage() < 50)
        try_bloodrage();

    try_heroic_strike();

    if (!pchar->action_ready())
        return;

    if (try_battle_shout())
        return;

    if (try_death_wish())
        return;

    if (try_execute())
        return;

    if (try_bloodthirst())
        return;

    if (try_whirlwind())
        return;
}

void WarriorSpells::mh_auto_attack(const int iteration) {
    if (!pchar->is_melee_attacking())
        pchar->start_attack();

    if (!mh_attack->attack_is_valid(iteration))
        return;

    if (pchar->get_hs_buff()->is_active() && heroic_strike->is_available(pchar->get_curr_rage())) {
        pchar->lose_rage(heroic_strike->perform(pchar->get_curr_rage()));
    }
    else {
        if (pchar->get_hs_buff()->is_active())
            pchar->get_hs_buff()->use_charge();

        pchar->gain_rage(mh_attack->perform(pchar->get_curr_rage()));

        if (pchar->action_ready()) {
            PlayerAction* new_event = new PlayerAction(this, pchar->get_engine()->get_current_priority() + 0.1);
            pchar->get_engine()->add_event(new_event);
        }
    }

    add_next_mh_attack();
}

void WarriorSpells::oh_auto_attack(const int iteration) {
    if (!pchar->is_melee_attacking())
        pchar->start_attack();

    if (!oh_attack->attack_is_valid(iteration))
        return;

    pchar->gain_rage(oh_attack->perform(pchar->get_curr_rage()));

    if (pchar->action_ready()) {
        PlayerAction* new_event = new PlayerAction(this, pchar->get_engine()->get_current_priority() + 0.1);
        pchar->get_engine()->add_event(new_event);
    }

    add_next_oh_attack();
}

void WarriorSpells::add_next_mh_attack(void) {
    MainhandMeleeHit* new_event = new MainhandMeleeHit(this, get_mh_attack()->get_next_expected_use(), get_mh_attack()->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

void WarriorSpells::add_next_oh_attack(void) {
    OffhandMeleeHit* new_event = new OffhandMeleeHit(this, oh_attack->get_next_expected_use(), oh_attack->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

MainhandAttack* WarriorSpells::get_mh_attack() const {
    return dynamic_cast<MainhandAttack*>(mh_attack);
}

OffhandAttack* WarriorSpells::get_oh_attack() const {
    return dynamic_cast<OffhandAttack*>(oh_attack);
}

Bloodthirst* WarriorSpells::get_bloodthirst() const {
    return this->bt;
}

DeepWounds* WarriorSpells::get_deep_wounds() const {
    return this->deep_wounds;
}

HeroicStrike* WarriorSpells::get_heroic_strike() const {
    return this->heroic_strike;
}

Execute* WarriorSpells::get_execute() const {
    return this->execute;
}

Overpower* WarriorSpells::get_overpower() const {
    return this->overpower;
}

OffhandAttackWarrior* WarriorSpells::get_oh_attack_warrior() const {
    return dynamic_cast<OffhandAttackWarrior*>(this->oh_attack);
}

DeathWish* WarriorSpells::get_death_wish() const {
    return this->death_wish;
}

BattleShout* WarriorSpells::get_battle_shout() const {
    return this->battle_shout;
}

BerserkerRage* WarriorSpells::get_berserker_rage() const {
    return this->berserker_rage;
}

Bloodrage* WarriorSpells::get_bloodrage() const {
    return this->bloodrage;
}

Whirlwind* WarriorSpells::get_whirlwind() const {
    return this->whirlwind;
}

void WarriorSpells::apply_deep_wounds() {
    deep_wounds->apply_debuff();
}

void WarriorSpells::try_berserker_rage() {
    if (berserker_rage->is_available(pchar->get_curr_rage()))
        pchar->gain_rage(berserker_rage->perform(pchar->get_curr_rage()));
}

void WarriorSpells::try_bloodrage() {
    if (bloodrage->is_available(pchar->get_curr_rage()))
        pchar->gain_rage(bloodrage->perform(pchar->get_curr_rage()));
}

void WarriorSpells::try_heroic_strike() {
    // TODO: Refactor this check into separate target mechanic.
    float time_remaining = 300 - pchar->get_engine()->get_current_priority();
    bool execute_phase = time_remaining / 300 > 0.8 ? true : false;

    if (execute_phase)
        return;

    if (pchar->get_curr_rage() > 50 && !pchar->get_hs_buff()->is_active())
        pchar->get_hs_buff()->apply_buff();
}

bool WarriorSpells::try_bloodthirst() {
    // TODO: Refactor this check into separate target mechanic.
    float time_remaining = 300 - pchar->get_engine()->get_current_priority();
    bool execute_phase = time_remaining / 300 > 0.8 ? true : false;

    if (execute_phase)
        return false;

    if (bt->is_enabled() && bt->is_available(pchar->get_curr_rage())) {
        pchar->lose_rage(bt->perform(pchar->get_curr_rage()));
        return true;
    }

    return false;
}

bool WarriorSpells::try_execute() {
    // TODO: Refactor this check into separate target mechanic.
    float time_remaining = 300 - pchar->get_engine()->get_current_priority();
    bool execute_phase = time_remaining / 300 > 0.8 ? true : false;

    if (execute_phase && execute->is_available(pchar->get_curr_rage())) {
        pchar->lose_rage(execute->perform(pchar->get_curr_rage()));
        return true;
    }

    return false;
}

bool WarriorSpells::try_overpower() {
    return false;
}

bool WarriorSpells::try_death_wish() {
    if (death_wish->is_enabled() && death_wish->is_available(pchar->get_curr_rage())) {
        pchar->lose_rage(death_wish->perform(pchar->get_curr_rage()));
        return true;
    }

    return false;
}

bool WarriorSpells::try_battle_shout() {
    if (!pchar->get_battle_shout_buff()->is_active() && battle_shout->is_available(pchar->get_curr_rage())) {
        pchar->lose_rage(battle_shout->perform(pchar->get_curr_rage()));
        return true;
    }

    return false;
}

bool WarriorSpells::try_whirlwind() {
    // TODO: Refactor this check into separate target mechanic.
    float time_remaining = 300 - pchar->get_engine()->get_current_priority();
    bool execute_phase = time_remaining / 300 > 0.8 ? true : false;

    if (execute_phase)
        return false;

    if (whirlwind->is_available(pchar->get_curr_rage())) {
        pchar->lose_rage(whirlwind->perform(pchar->get_curr_rage()));
        return true;
    }

    return false;
}
