
#include "Warrior.h"
#include "Talents.h"

#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Arms.h"
#include "Fury.h"
#include "Protection.h"
#include "Stats.h"
#include "Procs.h"
#include "Buffs.h"
#include "WarriorSpells.h"
#include "CharacterStats.h"
#include "WarriorStatistics.h"
#include "Race.h"
#include "Mainhand.h"
#include "Offhand.h"
#include <QDebug>

#include "Flurry.h"
#include "HeroicStrikeBuff.h"
#include "UnbridledWrath.h"
#include "DeathWishBuff.h"
#include "BattleShoutBuff.h"

Warrior::Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll, Faction *faction, QObject* parent) :
    Character(race, engine, _eq, _roll, faction, parent) {
    available_races.append("Dwarf");
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");
    available_races.append("Undead");

    // TODO: Investigate whether base stats below are the same for all melee classes.
    // Character sheet implies 3% base crit.
    // Crit without gear and no crit from base agil = 3 - (clvl * 5 - wpn-skill) * 0.04
    this->cstats->increase_crit(0.03);
    // Character sheet implies 160 base ap (not including base strength) at lvl 60.
    // Character sheet implies 10 base ap (not including base strength) at lvl 1.
    this->cstats->get_stats()->increase_base_melee_ap(160);

    // Constants added as a hack, these are the gains from 1-60.
    // This essentially forces a clvl of 60 for stats to be accurate for warrior.
    set_clvl(60);
    cstats->increase_strength(get_strength_modifier() + 97);
    cstats->increase_agility(get_agility_modifier() + 60);
    cstats->increase_stamina(get_stamina_modifier() + 88);
    cstats->increase_intellect(get_intellect_modifier() + 10);
    cstats->increase_spirit(get_spirit_modifier() + 25);
    cstats->get_stats()->set_melee_ap_per_agi(0);
    cstats->get_stats()->set_melee_ap_per_str(2);
    this->rage = 0;
    this->roll->set_character(this);

    cstats->get_equipment()->set_mainhand("Skullforge Reaver");
    cstats->get_equipment()->set_offhand("Frostbite");

    this->statistics = new WarriorStatistics();

    this->warr_spells = new WarriorSpells(this);
    this->spells = dynamic_cast<Spells*>(warr_spells);

    this->flurry = new Flurry(this);
    this->heroic_strike_buff = new HeroicStrikeBuff(this);
    this->death_wish_buff = new DeathWishBuff(this);
    this->battle_shout_buff = new BattleShoutBuff(this);

    buffs->add_buff(flurry);
    buffs->add_buff(heroic_strike_buff);
    buffs->add_buff(death_wish_buff);
    buffs->add_buff(battle_shout_buff);

    this->unbridled_wrath = new UnbridledWrath(engine, this, roll);
    procs->add_proc_effect(unbridled_wrath);

    spells->add_statistics();
    buffs->add_statistics();
    procs->add_statistics();
    initialize_talents();
}

Warrior::~Warrior() {
    delete warr_spells;
    delete statistics;
}

void Warrior::rotation() {
    warr_spells->rotation();
}

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

int Warrior::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

int Warrior::get_int_needed_for_one_percent_spell_crit() const {
    // TODO: Placeholder value
    return 20;
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
    return std::max(1, int(round(damage_dealt/30.7)));
}

Flurry* Warrior::get_flurry() const {
    return this->flurry;
}
HeroicStrikeBuff* Warrior::get_hs_buff() const {
    return this->heroic_strike_buff;
}
UnbridledWrath* Warrior::get_unbridled_wrath() const {
    return this->unbridled_wrath;
}
DeathWishBuff* Warrior::get_death_wish_buff() const {
    return this->death_wish_buff;
}
BattleShoutBuff* Warrior::get_battle_shout_buff() const {
    return this->battle_shout_buff;
}

float Warrior::global_cooldown() const {
    return 1.5;
}

int Warrior::get_curr_rage() const {
    return this->rage;
}

void Warrior::melee_mh_white_hit_effect() {
    flurry->use_charge();
    run_mh_white_specific_proc_effects();
}

void Warrior::melee_mh_yellow_hit_effect() {
    run_mh_yellow_specific_proc_effects();
}

void Warrior::melee_mh_white_critical_effect() {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();
    run_mh_white_specific_proc_effects();
}

void Warrior::melee_mh_yellow_critical_effect() {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();
    run_mh_yellow_specific_proc_effects();
}

void Warrior::melee_oh_white_hit_effect() {
    flurry->use_charge();
    run_oh_white_specific_proc_effects();
}

void Warrior::melee_oh_yellow_hit_effect() {
    run_oh_yellow_specific_proc_effects();
}

void Warrior::melee_oh_white_critical_effect() {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();
    run_oh_white_specific_proc_effects();
}

void Warrior::melee_oh_yellow_critical_effect() {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();
    run_oh_yellow_specific_proc_effects();
}

void Warrior::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new Arms(this), new Fury(this), new Protection(this));
    }
}

void Warrior::reset_resource() {
    rage = 0;
}

void Warrior::reset_spells() {
    warr_spells->reset();
}
