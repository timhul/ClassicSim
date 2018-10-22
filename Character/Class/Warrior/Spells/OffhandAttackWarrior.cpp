
#include "OffhandAttackWarrior.h"
#include "Warrior.h"
#include "DeepWounds.h"
#include "OverpowerBuff.h"
#include "RecklessnessBuff.h"
#include "CharacterStats.h"

OffhandAttackWarrior::OffhandAttackWarrior(Character* pchar) :
    OffhandAttack(pchar),
    TalentRequirer(5, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar))
{
    talent_ranks = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625};
    offhand_penalty = talent_ranks[curr_talent_rank];
}

void OffhandAttackWarrior::increase_talent_rank_effect(const QString&) {
    offhand_penalty = talent_ranks[curr_talent_rank];
}

void OffhandAttackWarrior::decrease_talent_rank_effect(const QString&) {
    offhand_penalty = talent_ranks[curr_talent_rank];
}

void OffhandAttackWarrior::extra_attack() {
    calculate_damage();
}

void OffhandAttackWarrior::spell_effect() {
    complete_swing();
    calculate_damage();
}

void OffhandAttackWarrior::calculate_damage() {
    const int oh_wpn_skill = warr->get_oh_wpn_skill();
    int result = roll->get_melee_hit_result(oh_wpn_skill, pchar->get_stats()->get_oh_crit_chance());

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }

    pchar->add_player_reaction_event();

    if (result == AttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return;
    }
    if (result == AttackResult::BLOCK || result == AttackResult::BLOCK_CRITICAL) {
        increment_full_block();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return;
    }

    if (warr->get_recklessness_buff()->is_active())
        result = AttackResult::CRITICAL;

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_oh_dmg() * offhand_penalty);

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(round(damage_dealt)));
        warr->melee_oh_white_critical_effect();
        // TODO: Save statistics for resource gains
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
        warr->gain_rage(rage_gained);
        return;
    }
    if (result == AttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(oh_wpn_skill));
        const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
        warr->melee_oh_white_hit_effect();
        // TODO: Save statistics for resource gains
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        warr->gain_rage(rage_gained);
        return;
    }

    warr->melee_oh_white_hit_effect();
    damage_dealt = round(damage_dealt);
    const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
    // TODO: Save statistics for resource gains
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
    warr->gain_rage(rage_gained);
}
