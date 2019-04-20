#include "WarriorSpells.h"

#include "Warrior.h"
#include "AngerManagement.h"
#include "BattleShout.h"
#include "BattleShoutBuff.h"
#include "BattleStance.h"
#include "BerserkerRage.h"
#include "BerserkerStance.h"
#include "Bloodrage.h"
#include "Bloodthirst.h"
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "DeepWounds.h"
#include "Engine.h"
#include "Execute.h"
#include "Flurry.h"
#include "Hamstring.h"
#include "HeroicStrike.h"
#include "Overpower.h"
#include "MainhandAttackWarrior.h"
#include "MainhandMeleeHit.h"
#include "MortalStrike.h"
#include "NoEffectBuff.h"
#include "OffhandAttackWarrior.h"
#include "OffhandMeleeHit.h"
#include "Recklessness.h"
#include "Rend.h"
#include "Slam.h"
#include "UnbridledWrath.h"
#include "Whirlwind.h"

WarriorSpells::WarriorSpells(Warrior* pchar) :
    CharacterSpells(pchar),
    warr(pchar)
{
    this->anger_management = new AngerManagement(pchar);
    this->battle_shout = new BattleShout(pchar);
    this->battle_stance = new BattleStance(pchar);
    this->berserker_rage = new BerserkerRage(pchar);
    this->berserker_stance = new BerserkerStance(pchar);
    this->bloodrage = new Bloodrage(pchar);
    this->bt = new Bloodthirst(pchar);
    this->death_wish = new DeathWish(pchar);
    this->deep_wounds = new DeepWounds(pchar);
    this->execute = new Execute(pchar);
    this->hamstring = new Hamstring(pchar);
    this->heroic_strike = new HeroicStrike(pchar);
    this->overpower = new Overpower(pchar);
    this->mortal_strike = new MortalStrike(pchar);
    this->recklessness = new Recklessness(pchar);
    this->rend = new Rend(pchar);
    this->slam = new Slam(pchar);
    this->whirlwind = new Whirlwind(pchar);

    this->warr_mh_attack = new MainhandAttackWarrior(pchar);
    this->warr_oh_attack = new OffhandAttackWarrior(pchar);

    add_spell(anger_management, NO_RELINK);
    add_spell(battle_shout, NO_RELINK);
    add_spell(battle_stance, NO_RELINK);
    add_spell(berserker_rage, NO_RELINK);
    add_spell(berserker_stance, NO_RELINK);
    add_spell(bloodrage, NO_RELINK);
    add_spell(bt, NO_RELINK);
    add_spell(death_wish, NO_RELINK);
    add_spell(deep_wounds, NO_RELINK);
    add_spell(execute, NO_RELINK);
    add_spell(hamstring, NO_RELINK);
    add_spell(heroic_strike, NO_RELINK);
    add_spell(overpower, NO_RELINK);
    add_spell(mortal_strike, NO_RELINK);
    add_spell(recklessness, NO_RELINK);
    add_spell(rend, NO_RELINK);
    add_spell(slam, NO_RELINK);
    add_spell(whirlwind, NO_RELINK);
    add_spell(warr_mh_attack, NO_RELINK);
    add_spell(warr_oh_attack, NO_RELINK);
}

void WarriorSpells::mh_auto_attack(const int iteration) {
    if (!warr_mh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    if (heroic_strike->is_queued() && heroic_strike->get_spell_status() == SpellStatus::Available) {
        heroic_strike->calculate_damage();
    }
    else {
        if (heroic_strike->is_queued())
            heroic_strike->cancel();

        warr_mh_attack->perform();
    }

    add_next_mh_attack();
}

void WarriorSpells::oh_auto_attack(const int iteration) {
    if (!warr_oh_attack->attack_is_valid(iteration))
        return;

    if (!is_melee_attacking())
        return;

    warr_oh_attack->perform();

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

AngerManagement* WarriorSpells::get_anger_management() const {
    return this->anger_management;
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

Hamstring* WarriorSpells::get_hamstring() const {
    return this->hamstring;
}

HeroicStrike* WarriorSpells::get_heroic_strike() const {
    return this->heroic_strike;
}

Execute* WarriorSpells::get_execute() const {
    return this->execute;
}

MortalStrike* WarriorSpells::get_mortal_strike() const {
    return this->mortal_strike;
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

Slam* WarriorSpells::get_slam() const {
    return this->slam;
}

Rend* WarriorSpells::get_rend() const {
    return this->rend;
}

Recklessness* WarriorSpells::get_recklessness() const {
    return this->recklessness;
}

void WarriorSpells::apply_deep_wounds() {
    deep_wounds->perform();
}
