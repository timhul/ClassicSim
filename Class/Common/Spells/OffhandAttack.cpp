#include "OffhandAttack.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "Equipment.h"
#include "OffhandMeleeHit.h"
#include "Weapon.h"

OffhandAttack::OffhandAttack(Character* pchar) :
    Spell("Offhand Attack",
          "Assets/items/Inv_sword_04.png",
          pchar,
          new CooldownControl(pchar, 1.0),
          RestrictedByGcd::No,
          ResourceType::Rage,
          0),
    offhand_penalty(0.5)
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

OffhandAttack::~OffhandAttack() {
    delete cooldown;
}

void OffhandAttack::extra_attack() {
    complete_swing();
    calculate_damage();
    add_next_oh_attack();
}

void OffhandAttack::spell_effect() {
    complete_swing();
    calculate_damage();
}

int OffhandAttack::calculate_damage() {
    const unsigned oh_wpn_skill = pchar->get_oh_wpn_skill();
    const int result = roll->get_melee_hit_result(oh_wpn_skill, pchar->get_stats()->get_oh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return result;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return result;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return result;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_non_normalized_oh_dmg() * offhand_penalty);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);

        pchar->melee_oh_white_critical_effect();
        return result;
    }

    pchar->melee_oh_white_hit_effect();

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(oh_wpn_skill);
        add_glancing_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        return result;
    }

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
    return result;
}

double OffhandAttack::get_next_expected_use() const {
    double curr_time = pchar->get_engine()->get_current_priority();
    return next_expected_use > curr_time ? next_expected_use : curr_time;
}

void OffhandAttack::update_next_expected_use(const double haste_change) {
    double curr_time = pchar->get_engine()->get_current_priority();
    double remainder_after_haste_change = (next_expected_use - curr_time);

    if (remainder_after_haste_change < -0.0001)
        return;

    if (haste_change < 0)
        remainder_after_haste_change *=  (1 + (-1) * haste_change);
    else
        remainder_after_haste_change /=  (1 + haste_change);

    next_expected_use = curr_time + remainder_after_haste_change;
}

void OffhandAttack::complete_swing() {
    cooldown->last_used = engine->get_current_priority();
    next_expected_use = cooldown->last_used + pchar->get_stats()->get_oh_wpn_speed();
}

void OffhandAttack::reset_swingtimer() {
    next_expected_use = pchar->get_engine()->get_current_priority() + pchar->get_stats()->get_oh_wpn_speed();
    if (pchar->get_spells()->is_melee_attacking())
        add_next_oh_attack();
}

void OffhandAttack::add_next_oh_attack() {
    auto* new_event = new OffhandMeleeHit(pchar->get_spells(), get_next_expected_use(), get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

bool OffhandAttack::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int OffhandAttack::get_next_iteration() {
    return ++iteration;
}

void OffhandAttack::reset_effect() {
    next_expected_use = 0;
}

void OffhandAttack::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_offhand() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_offhand()->get_value("icon");
    this->cooldown->base = pchar->get_stats()->get_oh_wpn_speed();

    reset();
}
