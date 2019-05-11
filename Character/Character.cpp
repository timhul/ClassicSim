#include "Character.h"

#include "AutoShot.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Engine.h"
#include "Equipment.h"
#include "Faction.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "PlayerAction.h"
#include "ProcInfo.h"
#include "Race.h"
#include "RulesetControl.h"
#include "SimSettings.h"
#include "Stats.h"
#include "Target.h"
#include "Utils/Check.h"
#include "Weapon.h"

Character::Character(QString class_name, Race* race, SimSettings *sim_settings) :
    class_name(std::move(class_name)),
    race(race),
    engine(new Engine()),
    target(new Target(63)),
    faction(new Faction(race)),
    talents(new CharacterTalents()),
    available_enchants(nullptr),
    cstats(nullptr),
    spells(nullptr),
    statistics(new ClassStatistics(sim_settings)),
    sim_settings(sim_settings),
    resource(nullptr),
    pet(nullptr),
    clvl(1),
    next_trinket_cd(-1),
    ruleset(Ruleset::Standard),
    mh_flat_dmg_bonus(0),
    oh_flat_dmg_bonus(0),
    ranged_flat_dmg_bonus(0)
{
    this->roll = new CombatRoll(this);
    this->enabled_procs = new EnabledProcs(this, faction);
    this->enabled_buffs = new EnabledBuffs(this, faction);
    this->next_gcd = 0 - this->global_cooldown();
}

Character::~Character() {
    delete engine;
    delete target;
    delete roll;
    delete faction;
    delete talents;
    delete enabled_procs;
    delete enabled_buffs;
    delete statistics;
}

QString Character::get_name() const {
    return this->class_name;
}

Race* Character::get_race() {
    return this->race;
}

bool Character::race_available(Race* race) const {
    return available_races.contains(race->get_name());
}

void Character::set_race(Race* race) {
    check(race_available(race), "Race not available");

    spells->deactivate_racials();
    this->race = race;
    spells->activate_racials();
}

void Character::change_target_creature_type(const QString &creature_type) {
    spells->deactivate_racials();
    target->set_creature_type(creature_type);
    spells->activate_racials();
}

void Character::switch_faction() {
    faction->switch_faction();
    enabled_procs->switch_faction();
    enabled_buffs->switch_faction();
}

int Character::get_clvl() const {
    return this->clvl;
}

void Character::set_clvl(const int clvl) {
    this->clvl = clvl;
}

bool Character::is_dual_wielding() {
    return cstats->get_equipment()->is_dual_wielding();
}

Engine* Character::get_engine() const {
    return this->engine;
}

Target* Character::get_target() const {
    return this->target;
}

CombatRoll* Character::get_combat_roll() const {
    return this->roll;
}

Faction* Character::get_faction() const {
    return this->faction;
}

Pet *Character::get_pet() const {
    return pet;
}

Equipment* Character::get_equipment() const {
    return this->cstats->get_equipment();
}

CharacterTalents* Character::get_talents() const {
    return this->talents;
}

EnabledBuffs* Character::get_enabled_buffs() const {
    return this->enabled_buffs;
}

CharacterSpells* Character::get_spells() const {
    return this->spells;
}

CharacterEnchants* Character::get_enchants() const {
    return this->available_enchants;
}

CharacterStats* Character::get_stats() const {
    return this->cstats;
}

ClassStatistics* Character::get_statistics() const {
    return this->statistics;
}

ClassStatistics* Character::relinquish_ownership_of_statistics() {
    ClassStatistics* tmp = this->statistics;
    this->statistics = new ClassStatistics(sim_settings);
    return tmp;
}

EnabledProcs* Character::get_enabled_procs() const {
    return this->enabled_procs;
}

SimSettings* Character::get_sim_settings() const {
    return this->sim_settings;
}

void Character::add_player_reaction_event() {
    auto* new_event = new PlayerAction(spells, engine->get_current_priority() + 0.1);
    engine->add_event(new_event);
}

void Character::add_pet_reaction_event() {

}

void Character::start_global_cooldown() {
    check(action_ready(), "Action not ready");
    this->next_gcd = engine->get_current_priority() + global_cooldown();
}

double Character::global_cooldown() const {
    return 1.5;
}

bool Character::on_global_cooldown() const {
    return engine->get_current_priority() < this->next_gcd;
}

void Character::start_trinket_cooldown(const double trinket_duration) {
    this->next_trinket_cd = engine->get_current_priority() + trinket_duration;
}

bool Character::on_trinket_cooldown() const {
    return engine->get_current_priority() < next_trinket_cd;
}

bool Character::action_ready() const {
    // Allow some rounding errors (this could effectively speed up gcd by 1/10000ths of a second).
    double delta = next_gcd - engine->get_current_priority();
    return delta < 0.0001 && !spells->cast_in_progress();
}

void Character::melee_mh_white_hit_effect() {
    enabled_procs->run_proc_check(ProcInfo::Source::MainhandSwing);
}

void Character::melee_mh_white_critical_effect() {
    melee_mh_white_hit_effect();
}

void Character::melee_mh_yellow_hit_effect() {
    enabled_procs->run_proc_check(ProcInfo::Source::MainhandSpell);
}

void Character::melee_mh_yellow_critical_effect() {
    melee_mh_yellow_hit_effect();
}

void Character::melee_oh_white_hit_effect() {
    enabled_procs->run_proc_check(ProcInfo::Source::OffhandSwing);
}

void Character::melee_oh_white_critical_effect() {
    melee_oh_white_hit_effect();
}

void Character::ranged_white_hit_effect() {
    enabled_procs->run_proc_check(ProcInfo::Source::RangedAutoShot);
}

void Character::ranged_yellow_hit_effect() {
    enabled_procs->run_proc_check(ProcInfo::Source::RangedSpell);
}

void Character::spell_hit_effect() {

}

void Character::spell_critical_effect() {

}

double Character::get_random_normalized_mh_dmg() {
    Weapon* mh = cstats->get_equipment()->get_mainhand();
    return get_normalized_dmg(mh->get_random_dmg() + mh_flat_dmg_bonus, mh);
}

double Character::get_random_non_normalized_mh_dmg() {
    Weapon* mh = cstats->get_equipment()->get_mainhand();
    return get_non_normalized_dmg(mh->get_random_dmg() + mh_flat_dmg_bonus,
                                  cstats->get_melee_ap(),
                                  mh->get_base_weapon_speed());
}

double Character::get_random_normalized_oh_dmg() {
    Weapon* oh = cstats->get_equipment()->get_offhand();
    return get_normalized_dmg(oh->get_random_dmg() + oh_flat_dmg_bonus, oh);
}

double Character::get_random_non_normalized_oh_dmg() {
    Weapon* oh = cstats->get_equipment()->get_offhand();
    return get_non_normalized_dmg(oh->get_random_dmg() + oh_flat_dmg_bonus,
                                  cstats->get_melee_ap(),
                                  oh->get_base_weapon_speed());
}

double Character::get_random_normalized_ranged_dmg() {
    Weapon* ranged = cstats->get_equipment()->get_ranged();
    return get_normalized_dmg(ranged->get_random_dmg() + ranged_flat_dmg_bonus, ranged);
}

double Character::get_random_non_normalized_ranged_dmg() {
    Weapon* ranged = cstats->get_equipment()->get_ranged();
    return get_non_normalized_dmg(ranged->get_random_dmg() + ranged_flat_dmg_bonus,
                                  cstats->get_ranged_ap(),
                                  ranged->get_base_weapon_speed());
}

unsigned Character::get_avg_mh_damage() {
    if (!has_mainhand())
        return static_cast<unsigned>(round(get_normalized_dmg(1, nullptr)));

    unsigned attack_power = cstats->get_melee_ap();
    Weapon* mh = cstats->get_equipment()->get_mainhand();
    auto avg_dmg = static_cast<unsigned>(round(mh->get_min_dmg() + mh->get_max_dmg() + mh_flat_dmg_bonus) / 2);
    return static_cast<unsigned>(round(get_non_normalized_dmg(avg_dmg, attack_power, mh->get_base_weapon_speed())));
}

double Character::get_normalized_dmg(const unsigned damage, const Weapon* weapon) {
    unsigned attack_power = cstats->get_melee_ap();
    if (weapon == nullptr)
        return get_non_normalized_dmg(damage, attack_power, 2.0);

    double normalized_wpn_speed = -1;

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
        attack_power = cstats->get_ranged_ap();
        break;
    default:
        check(false, "Character::get_normalized_dmg reached end of switch");
    }

    return get_non_normalized_dmg(damage, attack_power, normalized_wpn_speed);
}

double Character::get_non_normalized_dmg(const unsigned damage, const unsigned attack_power, const double wpn_speed) {
    return damage + (wpn_speed * attack_power / 14);
}

int Character::get_mh_wpn_skill() const {
    return cstats->get_mh_wpn_skill();
}

int Character::get_oh_wpn_skill() const {
    return cstats->get_oh_wpn_skill();
}

int Character::get_ranged_wpn_skill() const {
    return cstats->get_ranged_wpn_skill();
}

void Character::increase_melee_attack_speed(unsigned increase) {
    cstats->increase_melee_attack_speed(increase);
    double increase_double = double(increase) / 100;

    spells->get_mh_attack()->update_next_expected_use(increase_double);
    spells->add_next_mh_attack();

    if (cstats->get_equipment()->is_dual_wielding()) {
        spells->get_oh_attack()->update_next_expected_use(increase_double);
        spells->add_next_oh_attack();
    }
}

void Character::decrease_melee_attack_speed(unsigned decrease) {
    cstats->decrease_melee_attack_speed(decrease);
    double decrease_double = double(decrease) / 100;

    spells->get_mh_attack()->update_next_expected_use(-decrease_double);
    spells->add_next_mh_attack();

    if (cstats->get_equipment()->is_dual_wielding()) {
        spells->get_oh_attack()->update_next_expected_use(-decrease_double);
        spells->add_next_oh_attack();
    }
}

void Character::increase_ranged_attack_speed(unsigned increase) {
    cstats->increase_ranged_attack_speed(increase);
    double increase_double = double(increase) / 100;

    AutoShot* auto_shot = spells->get_auto_shot();
    if (auto_shot != nullptr) {
        auto_shot->update_next_expected_use(increase_double);
        spells->add_next_ranged_attack();
    }
}

void Character::decrease_ranged_attack_speed(unsigned decrease) {
    cstats->decrease_ranged_attack_speed(decrease);
    double decrease_double = double(decrease) / 100;

    AutoShot* auto_shot = spells->get_auto_shot();
    if (auto_shot != nullptr) {
        auto_shot->update_next_expected_use(-decrease_double);
        spells->add_next_ranged_attack();
    }
}

bool Character::has_mainhand() const {
    return cstats->get_equipment()->get_mainhand() != nullptr;
}

bool Character::has_offhand() const {
    return cstats->get_equipment()->get_offhand() != nullptr;
}

bool Character::has_ranged() const {
    return cstats->get_equipment()->get_ranged() != nullptr;
}

void Character::gain_mana(const unsigned) {

}

void Character::lose_mana(const unsigned) {

}

void Character::gain_rage(const unsigned) {

}

void Character::lose_rage(const unsigned) {

}

void Character::gain_energy(const unsigned) {

}

void Character::lose_energy(const unsigned) {

}

void Character::gain_focus(const unsigned) {

}

void Character::lose_focus(const unsigned) {

}

void Character::increase_base_mana(const unsigned) {

}

void Character::decrease_base_mana(const unsigned) {

}

double Character::get_mp5_from_spirit() const {
    check(false, "Not implemented");
    return 0.0;
}

void Character::reset_resource() {
    this->resource->reset_resource();
}

void Character::increase_mh_flat_damage_bonus(const unsigned change) {
    this->mh_flat_dmg_bonus += change;
}

void Character::decrease_mh_flat_damage_bonus(const unsigned change) {
    check((mh_flat_dmg_bonus >= change), "Underflow decrease");
    this->mh_flat_dmg_bonus -= change;
}

void Character::increase_oh_flat_damage_bonus(const unsigned change) {
    this->oh_flat_dmg_bonus += change;
}

void Character::decrease_oh_flat_damage_bonus(const unsigned change) {
    check((oh_flat_dmg_bonus >= change), "Underflow decrease");
    this->oh_flat_dmg_bonus -= change;
}

void Character::increase_ranged_flat_damage_bonus(const unsigned change) {
    this->ranged_flat_dmg_bonus += change;
}

void Character::decrease_ranged_flat_damage_bonus(const unsigned change) {
    check((ranged_flat_dmg_bonus >= change), "Underflow decrease");
    this->ranged_flat_dmg_bonus -= change;
}

void Character::reset() {
    reset_class_specific();

    next_gcd = 0 - this->global_cooldown();
    next_trinket_cd = -1;

    enabled_buffs->reset();
    spells->reset();
    enabled_procs->reset();

    reset_resource();

    sim_settings->use_ruleset(this->ruleset, this);
}

void Character::prepare_set_of_combat_iterations() {
    statistics->prepare_statistics();
    engine->prepare_set_of_iterations(statistics->get_engine_statistics());
    this->ruleset = sim_settings->get_ruleset();
    sim_settings->use_ruleset(this->ruleset, this);
    spells->prepare_set_of_combat_iterations();
    enabled_buffs->prepare_set_of_combat_iterations();
    enabled_procs->prepare_set_of_combat_iterations();
}
