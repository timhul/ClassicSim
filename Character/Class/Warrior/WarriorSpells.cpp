
#include "WarriorSpells.h"
#include "Warrior.h"

#include "PlayerAction.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"

#include "BattleShout.h"
#include "BattleStance.h"
#include "BerserkerRage.h"
#include "BerserkerStance.h"
#include "Bloodrage.h"
#include "Bloodthirst.h"
#include "DeathWish.h"
#include "DeepWounds.h"
#include "Execute.h"
#include "HeroicStrike.h"
#include "Overpower.h"
#include "Recklessness.h"
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
    warr(pchar)
{
    this->battle_shout = new BattleShout(pchar);
    this->battle_stance = new BattleStance(pchar);
    this->berserker_rage = new BerserkerRage(pchar);
    this->berserker_stance = new BerserkerStance(pchar);
    this->bloodrage = new Bloodrage(pchar);
    this->bt = new Bloodthirst(pchar);
    this->death_wish = new DeathWish(pchar);
    this->deep_wounds = new DeepWounds(pchar);
    this->execute = new Execute(pchar);
    this->heroic_strike = new HeroicStrike(pchar);
    this->overpower = new Overpower(pchar);
    this->recklessness = new Recklessness(pchar);
    this->whirlwind = new Whirlwind(pchar);

    this->warr_mh_attack = new MainhandAttackWarrior(pchar);
    this->warr_oh_attack = new OffhandAttackWarrior(pchar);

    spells.append(battle_shout);
    spells.append(battle_stance);
    spells.append(berserker_rage);
    spells.append(berserker_stance);
    spells.append(bloodrage);
    spells.append(bt);
    spells.append(death_wish);
    spells.append(deep_wounds);
    spells.append(execute);
    spells.append(heroic_strike);
    spells.append(overpower);
    spells.append(recklessness);
    spells.append(whirlwind);
    spells.append(warr_mh_attack);
    spells.append(warr_oh_attack);
}

WarriorSpells::~WarriorSpells() = default;

void WarriorSpells::reset() {
    for (auto & spell : spells) {
        spell->reset();
    }
}

void WarriorSpells::mh_auto_attack(const int iteration) {
    if (!warr_mh_attack->attack_is_valid(iteration))
        return;

    if (warr->get_hs_buff()->is_active() && heroic_strike->is_available()) {
        heroic_strike->calculate_damage();
    }
    else {
        if (warr->get_hs_buff()->is_active())
            warr->get_hs_buff()->use_charge();

        warr_mh_attack->perform();

        if (warr->action_ready()) {
            auto* new_event = new PlayerAction(warr->get_rotation(), warr->get_engine()->get_current_priority() + 0.1);
            warr->get_engine()->add_event(new_event);
        }
    }

    add_next_mh_attack();
}

void WarriorSpells::oh_auto_attack(const int iteration) {
    if (!warr_oh_attack->attack_is_valid(iteration))
        return;

    warr_oh_attack->perform();

    if (warr->action_ready()) {
        auto* new_event = new PlayerAction(warr->get_rotation(), warr->get_engine()->get_current_priority() + 0.1);
        warr->get_engine()->add_event(new_event);
    }

    add_next_oh_attack();
}

void WarriorSpells::add_next_mh_attack() {
    auto* new_event = new MainhandMeleeHit(this, get_mh_attack()->get_next_expected_use(), get_mh_attack()->get_next_iteration());
    warr->get_engine()->add_event(new_event);
}

void WarriorSpells::add_next_oh_attack() {
    auto* new_event = new OffhandMeleeHit(this, warr_oh_attack->get_next_expected_use(), warr_oh_attack->get_next_iteration());
    warr->get_engine()->add_event(new_event);
}

MainhandAttack* WarriorSpells::get_mh_attack() const {
    return dynamic_cast<MainhandAttack*>(warr_mh_attack);
}

OffhandAttack* WarriorSpells::get_oh_attack() const {
    return dynamic_cast<OffhandAttack*>(warr_oh_attack);
}

BattleStance* WarriorSpells::get_battle_stance() const {
    return this->battle_stance;
}

BerserkerStance* WarriorSpells::get_berserker_stance() const {
    return this->berserker_stance;
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
    return dynamic_cast<OffhandAttackWarrior*>(this->warr_oh_attack);
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

Recklessness* WarriorSpells::get_recklessness() const {
    return this->recklessness;
}

void WarriorSpells::apply_deep_wounds() {
    deep_wounds->apply_debuff();
}
