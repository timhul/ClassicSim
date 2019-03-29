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
                     3000),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Aimed Shot", 1, DisabledAtZero::Yes),
                                                new TalentRequirerInfo("Efficiency", 5, DisabledAtZero::No),
                                                new TalentRequirerInfo("Mortal Shots", 5, DisabledAtZero::No)})
{
    this->enabled = false;
    resource_base = resource_cost;
    efficiency_ranks = {
        1.0, 0.98, 0.96, 0.94, 0.92, 0.90
    };
    mortal_shots_bonus = 0.0;
    mortal_shots_ranks = {
        0.0, 0.06, 0.12, 0.18, 0.24, 0.30
    };
}

void AimedShot::spell_effect() {
    pchar->get_spells()->stop_attack();
    add_gcd_event();
    start_cast();
}

void AimedShot::complete_cast_effect() {
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
        damage_dealt *= pchar->get_stats()->get_ranged_ability_crit_dmg_mod() + mortal_shots_bonus;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        pchar->ranged_yellow_critical_effect(true);
        return;
    }

    pchar->ranged_yellow_hit_effect(true);
    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

void AimedShot::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Efficiency")
        resource_cost = static_cast<int>(round(resource_base * efficiency_ranks[curr]));
    if (talent_name == "Mortal Shots")
        mortal_shots_bonus = mortal_shots_ranks[curr];
}

void AimedShot::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Efficiency")
        resource_cost = static_cast<int>(round(resource_base * efficiency_ranks[curr]));
    if (talent_name == "Mortal Shots")
        mortal_shots_bonus = mortal_shots_ranks[curr];
}
