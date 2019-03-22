#include "MultiShot.h"

#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"

MultiShot::MultiShot(Character* pchar) :
    Spell("Multi-Shot",
          "Assets/ability/Ability_upgrademoonglaive.png",
          pchar,
          RestrictedByGcd::Yes,
          10.0,
          ResourceType::Mana,
          230)
{}

void MultiShot::spell_effect() {
    const int wpn_skill = pchar->get_ranged_wpn_skill();
    const int result = roll->get_ranged_ability_result(wpn_skill, pchar->get_stats()->get_ranged_crit_chance());

    add_gcd_event();
    pchar->lose_mana(static_cast<unsigned>(resource_cost));

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_normalized_ranged_dmg() + 150);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= 2;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_white_critical_effect(true);
        return;
    }

    pchar->ranged_white_hit_effect(true);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}
