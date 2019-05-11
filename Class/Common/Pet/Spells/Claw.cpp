#include "Claw.h"

#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Pet.h"
#include "Random.h"

Claw::Claw(Character* pchar, Pet* pet) :
    Spell(QString("Claw (%1)").arg(pet->get_name()),
          "Assets/ability/Ability_druid_rake.png",
          pchar,
          RestrictedByGcd::No,
          0,
          ResourceType::Focus,
          25),
    pet(pet),
    dmg_roll(new Random(43, 60))
{
    this->pchar = pchar;
}

Claw::~Claw() {
    delete dmg_roll;
}

void Claw::spell_effect() {
    const int wpn_skill = pchar->get_clvl() * 5;
    const int result = roll->get_pet_ability_result(wpn_skill, pet->get_crit_chance());

    pet->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        pet->lose_resource(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        pet->lose_resource(static_cast<unsigned>(resource_cost * 0.25));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        pet->lose_resource(static_cast<unsigned>(resource_cost * 0.25));
        return;
    }

    pet->lose_resource(resource_cost);

    double damage_dealt = damage_after_modifiers(dmg_roll->get_roll()) * pet->get_damage_modifier();

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pet->melee_critical_effect();
        return;
    }

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}
