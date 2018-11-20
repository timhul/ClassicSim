
#include "HeroicStrike.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Flurry.h"
#include "DeepWounds.h"
#include "HeroicStrikeBuff.h"
#include "MainhandAttackWarrior.h"
#include "OverpowerBuff.h"
#include "CharacterStats.h"

HeroicStrike::HeroicStrike(Character* pchar) :
    Spell("Heroic Strike", "Assets/warrior/arms/tier1/Ability_rogue_ambush.png", pchar, RestrictedByGcd::No, 0, ResourceType::Rage, 15),
    TalentRequirer(3, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar))
{
    spell_ranks = {11, 21, 32, 44, 58, 80, 111, 138, 157};
    spell_rank = 8;
    additional_dmg = spell_ranks[spell_rank];

    talent_ranks = {15, 14, 13, 12};
}

void HeroicStrike::calculate_damage() {
    warr->get_hs_buff()->use_charge();
    warr->get_spells()->get_mh_attack()->complete_swing();

    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    if (result == AttackResult::MISS) {
        increment_miss();
        warr->lose_rage(resource_cost);
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<int>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<int>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_mh_dmg() + additional_dmg);

    if (result == AttackResult::CRITICAL) {
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * warr->get_ability_crit_dmg_mod())), resource_cost, 0);
    }
    else if (result == AttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
    }

    warr->lose_rage(resource_cost);
}

void HeroicStrike::spell_effect() {
    warr->get_hs_buff()->apply_buff();
}

void HeroicStrike::increase_talent_rank_effect(const QString&) {
    resource_cost = talent_ranks[curr_talent_rank];
}

void HeroicStrike::decrease_talent_rank_effect(const QString&) {
    resource_cost = talent_ranks[curr_talent_rank];
}
