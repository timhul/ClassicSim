#include "AimedShot.h"

#include "AutoShot.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"

AimedShot::AimedShot(Character* pchar) :
    SpellCastingTime("Aimed Shot",
                     "Assets/items/Inv_spear_07.png",
                     pchar,
                     RestrictedByGcd::Yes,
                     10.0,
                     ResourceType::Mana,
                     310,
                     3000)
{}

void AimedShot::spell_effect() {
    pchar->get_spells()->stop_attack();
    add_gcd_event();
    start_cast();
}

void AimedShot::complete_cast_effect() {
    pchar->get_spells()->get_auto_shot()->continue_shot();
    pchar->get_spells()->start_attack();

    pchar->lose_mana(static_cast<unsigned>(resource_cost));
    const int wpn_skill = pchar->get_ranged_wpn_skill();
    const int result = roll->get_ranged_ability_result(wpn_skill, pchar->get_stats()->get_ranged_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_normalized_ranged_dmg() + 600);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_white_critical_effect(true);
        return;
    }

    pchar->ranged_white_hit_effect(true);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}
