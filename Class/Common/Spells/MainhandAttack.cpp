#include "MainhandAttack.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "Equipment.h"
#include "MainhandMeleeHit.h"
#include "Weapon.h"

MainhandAttack::MainhandAttack(Character* pchar) :
    Spell("Mainhand Attack", "", pchar, new CooldownControl(pchar, 1.0), RestrictedByGcd::No, ResourceType::Rage, 0) {
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

MainhandAttack::~MainhandAttack() {
    delete cooldown;
}

void MainhandAttack::extra_attack() {
    complete_swing();
    calculate_damage();
    add_next_mh_attack();
}

void MainhandAttack::spell_effect() {
    complete_swing();
    calculate_damage();
}

void MainhandAttack::calculate_damage() {
    pchar->add_player_reaction_event();

    const unsigned mh_wpn_skill = pchar->get_mh_wpn_skill();
    const int result = roll->get_melee_hit_result(mh_wpn_skill, pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS)
        return increment_miss();
    if (result == PhysicalAttackResult::DODGE)
        return increment_dodge();
    if (result == PhysicalAttackResult::PARRY)
        return increment_parry();

    double damage_dealt = damage_after_modifiers(pchar->get_random_non_normalized_mh_dmg());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->melee_mh_white_critical_effect();
        return;
    }

    pchar->melee_mh_white_hit_effect();

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(mh_wpn_skill);
        add_glancing_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        return;
    }

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double MainhandAttack::get_next_expected_use() const {
    double curr_time = pchar->get_engine()->get_current_priority();
    return next_expected_use > curr_time ? next_expected_use : curr_time;
}

void MainhandAttack::update_next_expected_use_for_parry() {
  // This comes from https://github.com/magey/classic-warrior/wiki/Parry-haste
  // The formula seems to be for player->boss parry haste. The graph
  // makes it seems like the 0.6 paramater goes to 0.5, so I'll just
  // use that here.
  double speed = pchar->get_stats()->get_mh_wpn_speed();
  double parry_haste_boost = 0.4 * speed;
  double curr_time = pchar->get_engine()->get_current_priority();

  double remaining = next_expected_use - curr_time;

  if (remaining / speed > 0.5)
    next_expected_use = cooldown->last_used + speed - parry_haste_boost;
  else if (remaining / speed < 0.2)
    ;
  else
    next_expected_use = next_expected_use - 0.2 * speed;
}

void MainhandAttack::update_next_expected_use(const double haste_change) {
    double curr_time = pchar->get_engine()->get_current_priority();
    double remainder_after_haste_change = (next_expected_use - curr_time);

    if (remainder_after_haste_change < -0.0001)
        return;

    if (haste_change < 0)
        remainder_after_haste_change *= (1 + (-1) * haste_change);
    else
        remainder_after_haste_change /= (1 + haste_change);
    next_expected_use = curr_time + remainder_after_haste_change;
}

void MainhandAttack::complete_swing() {
    cooldown->last_used = engine->get_current_priority();
    next_expected_use = cooldown->last_used + pchar->get_stats()->get_mh_wpn_speed();
}

void MainhandAttack::reset_swingtimer() {
    next_expected_use = pchar->get_engine()->get_current_priority() + pchar->get_stats()->get_mh_wpn_speed();
    if (pchar->get_spells()->is_melee_attacking())
        add_next_mh_attack();
}

void MainhandAttack::add_next_mh_attack() {
    auto new_event = new MainhandMeleeHit(pchar->get_spells(), get_next_expected_use(), get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

bool MainhandAttack::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int MainhandAttack::get_next_iteration() {
    return ++iteration;
}

void MainhandAttack::reset_effect() {
    next_expected_use = 0;
}

void MainhandAttack::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_mainhand()->get_value("icon");
    this->cooldown->base = pchar->get_stats()->get_mh_wpn_speed();

    reset();
}
