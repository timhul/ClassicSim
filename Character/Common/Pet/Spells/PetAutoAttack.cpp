#include "PetAutoAttack.h"

#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Pet.h"
#include "Random.h"

PetAutoAttack::PetAutoAttack(Character* pchar, Pet* pet, const QString& icon) :
    Spell(QString("Melee Hit (%1)").arg(pet->get_name()),
          icon,
          pchar,
          RestrictedByGcd::No,
          0,
          ResourceType::Focus,
          0),
    pet(pet),
    dmg_roll(new Random(pet->get_min_dmg(), pet->get_max_dmg()))
{
    this->pchar = pchar;
    next_expected_use = 0;
    iteration = 0;
}

PetAutoAttack::~PetAutoAttack() {
    delete dmg_roll;
}

void PetAutoAttack::spell_effect() {
    complete_swing();
    calculate_damage();
}

void PetAutoAttack::calculate_damage() {
    const int wpn_skill = pchar->get_clvl() * 5;
    const int result = roll->get_pet_hit_result(wpn_skill, pet->get_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return;
    }

    double damage_dealt = damage_after_modifiers(dmg_roll->get_roll()) * pet->get_damage_modifier();

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        return;
    }

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(wpn_skill);
        add_glancing_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        return;
    }

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

double PetAutoAttack::get_next_expected_use() const {
    double curr_time = pchar->get_engine()->get_current_priority();
    return next_expected_use > curr_time ? next_expected_use : curr_time;
}

void PetAutoAttack::update_next_expected_use(const double haste_change) {
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

void PetAutoAttack::complete_swing() {
    last_used = engine->get_current_priority();
    next_expected_use = last_used + pet->get_attack_speed();
}

bool PetAutoAttack::attack_is_valid(const int iteration) const {
    return this->iteration == iteration;
}

int PetAutoAttack::get_next_iteration() {
    return ++iteration;
}

void PetAutoAttack::reset_effect() {
    next_expected_use = 0;
}

void PetAutoAttack::prepare_set_of_combat_iterations_spell_specific() {
    this->cooldown = pet->get_attack_speed();

    reset();
}
