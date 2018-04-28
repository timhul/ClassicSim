
#include "Warrior.h"
#include "Talents.h"
#include "PlayerAction.h"
#include "Bloodthirst.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "Flurry.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Arms.h"
#include "Fury.h"
#include "Protection.h"
#include "Stats.h"
#include "Race.h"
#include "Mainhand.h"
#include "Offhand.h"
#include "DeepWounds.h"
#include "HeroicStrike.h"
#include "HeroicStrikeBuff.h"
#include "Execute.h"
#include "Overpower.h"
#include "UnbridledWrath.h"
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "BattleShout.h"
#include "BattleShoutBuff.h"
#include "BerserkerRage.h"
#include "Whirlwind.h"
#include <QDebug>

Warrior::Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, QObject* parent) :
    Character(race, engine, _eq, _roll, parent) {
    // Constants added as a hack, these are the gains from 1-60.
    // This essentially forces a clvl of 60 for stats to be accurate for warrior.
    set_clvl(60);
    base_stats->increase_str(race->get_base_strength() + get_strength_modifier() + 97);
    base_stats->increase_agi(race->get_base_agility() + get_agility_modifier() + 60);
    base_stats->increase_stam(race->get_base_stamina() + get_stamina_modifier() + 88);
    base_stats->increase_int(race->get_base_intellect() + get_intellect_modifier() + 10);
    base_stats->increase_spi(race->get_base_spirit() + get_spirit_modifier() + 25);
    base_stats->set_melee_ap_per_agi(0);
    base_stats->set_melee_ap_per_str(2);
    this->rage = 0;
    this->roll->set_character(this);

    equipment->set_mainhand("Skullforge Reaver");
    equipment->set_offhand("Frostbite");

    // TODO: For now mainhand/offhand attack must be initialized after equipment is set.
    // Fix so that equipment changes updates these spells.
    this->bt = new Bloodthirst(engine, this, roll);
    this->mh_attack = new MainhandAttackWarrior(engine, this, roll);
    this->oh_attack = new OffhandAttackWarrior(engine, this, roll);
    this->deep_wounds = new DeepWounds(engine, this, roll);
    this->heroic_strike = new HeroicStrike(engine, this, roll);
    this->execute = new Execute(engine, this, roll);
    this->overpower = new Overpower(engine, this, roll);
    this->unbridled_wrath = new UnbridledWrath(engine, this, roll);
    this->death_wish = new DeathWish(engine, this, roll);
    this->battle_shout = new BattleShout(engine, this, roll);
    this->berserker_rage = new BerserkerRage(engine, this, roll);
    this->whirlwind = new Whirlwind(engine, this, roll);
    spells = {bt, mh_attack, oh_attack, deep_wounds, heroic_strike, execute, overpower,
              unbridled_wrath, death_wish, battle_shout, berserker_rage, whirlwind};

    initialize_talents();

    this->flurry = new Flurry(this);
    this->heroic_strike_buff = new HeroicStrikeBuff(this);
    this->death_wish_buff = new DeathWishBuff(this);
    this->battle_shout_buff = new BattleShoutBuff(this);
    buffs = {flurry, heroic_strike_buff, death_wish_buff, battle_shout_buff};
}

Warrior::~Warrior() {}

QString Warrior::get_name(void) const {
    return "Warrior";
}

QString Warrior::get_class_color() const {
    return "#C79C6E";
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

int Warrior::get_ap_per_strength() const {
    return 2;
}

int Warrior::get_ap_per_agi() const {
    return 0;
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
    if (!is_melee_attacking()) {
        start_attack();
    }

    if (rage < 50 && berserker_rage->is_available(rage))
        gain_rage(berserker_rage->perform(rage));

    if (rage > 50 && !heroic_strike_buff->is_active())
        heroic_strike_buff->apply_buff();

    if (!action_ready()) {
        return;
    }

    if (!battle_shout_buff->is_active() && battle_shout->is_available(rage))
        lose_rage(battle_shout->perform(rage));

    else if (death_wish->is_enabled() && death_wish->is_available(rage))
        lose_rage(death_wish->perform(rage));

    else if (bt->is_enabled() && bt->is_available(rage))
        lose_rage(bt->perform(rage));

    // TODO: Check if execute is available. Requires target health.

}

void Warrior::mh_auto_attack(const int iteration) {
    if (!is_melee_attacking())
        start_attack();

    if (!mh_attack->attack_is_valid(iteration))
        return;

    if (heroic_strike_buff->is_active() && heroic_strike->is_available(rage)) {
        lose_rage(heroic_strike->perform(rage));
    }
    else {
        if (heroic_strike_buff->is_active())
            heroic_strike_buff->use_charge();

        gain_rage(mh_attack->perform(rage));

        if (action_ready()) {
            PlayerAction* new_event = new PlayerAction(this, 0.1);
            this->get_engine()->add_event(new_event);
        }
    }

    add_next_mh_attack();
}

void Warrior::oh_auto_attack(const int iteration) {
    if (!is_melee_attacking())
        start_attack();

    if (!oh_attack->attack_is_valid(iteration))
        return;

    gain_rage(oh_attack->perform(rage));

    if (action_ready()) {
        PlayerAction* new_event = new PlayerAction(this, 0.1);
        this->get_engine()->add_event(new_event);
    }

    add_next_oh_attack();
}

float Warrior::global_cooldown() const {
    return 1.5;
}

int Warrior::get_curr_rage() const {
    return this->rage;
}

Bloodthirst* Warrior::get_bloodthirst() const {
    return this->bt;
}

Flurry* Warrior::get_flurry() const {
    return this->flurry;
}

DeepWounds* Warrior::get_deep_wounds() const {
    return this->deep_wounds;
}

HeroicStrike* Warrior::get_heroic_strike() const {
    return this->heroic_strike;
}

HeroicStrikeBuff* Warrior::get_hs_buff() const {
    return this->heroic_strike_buff;
}

Execute* Warrior::get_execute() const {
    return this->execute;
}

Overpower* Warrior::get_overpower() const {
    return this->overpower;
}

OffhandAttackWarrior* Warrior::get_oh_attack_warrior() const {
    return dynamic_cast<OffhandAttackWarrior*>(this->oh_attack);
}

UnbridledWrath* Warrior::get_unbridled_wrath() const {
    return this->unbridled_wrath;
}

DeathWish* Warrior::get_death_wish() const {
    return this->death_wish;
}

DeathWishBuff* Warrior::get_death_wish_buff() const {
    return this->death_wish_buff;
}

BattleShout* Warrior::get_battle_shout() const {
    return this->battle_shout;
}

BattleShoutBuff* Warrior::get_battle_shout_buff() const {
    return this->battle_shout_buff;
}

BerserkerRage* Warrior::get_berserker_rage() const {
    return this->berserker_rage;
}

Whirlwind* Warrior::get_whirlwind() const {
    return this->whirlwind;
}

void Warrior::melee_critical_effect() {
    flurry->apply_buff();
    deep_wounds->apply_debuff();
}

void Warrior::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new Arms(this), new Fury(this), new Protection(this));
    }
}

void Warrior::reset_resource() {
    rage = 0;
}
