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
          230),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Efficiency", 5, DisabledAtZero::No)})
{
    resource_base = resource_cost;
    efficiency_ranks = {
        1.0, 0.98, 0.96, 0.94, 0.92, 0.90
    };
}

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
        damage_dealt *= pchar->get_stats()->get_ranged_ability_crit_dmg_mod();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_white_critical_effect(true);
        return;
    }

    pchar->ranged_white_hit_effect(true);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

void MultiShot::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Efficiency")
        resource_cost = static_cast<int>(round(resource_base * efficiency_ranks[curr]));
}

void MultiShot::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Efficiency")
        resource_cost = static_cast<int>(round(resource_base * efficiency_ranks[curr]));
}
