
#include "OffhandAttackWarrior.h"
#include "Warrior.h"
#include "DeepWounds.h"
#include "OverpowerBuff.h"
#include "RecklessnessBuff.h"

OffhandAttackWarrior::OffhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll) :
    OffhandAttack(engine,
                  pchar,
                  roll)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625};
}

void OffhandAttackWarrior::extra_attack() {
    calculate_damage();
}

void OffhandAttackWarrior::spell_effect() {
    complete_swing();
    calculate_damage();
}

void OffhandAttackWarrior::calculate_damage() {
    const int oh_wpn_skill = pchar->get_oh_wpn_skill();
    int result = roll->get_melee_hit_result(oh_wpn_skill);

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        pchar->get_overpower_buff()->apply_buff();
        pchar->gain_rage(pchar->rage_gained_from_dd(pchar->get_avg_mh_damage()));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        pchar->gain_rage(pchar->rage_gained_from_dd(pchar->get_avg_mh_damage()));
        return;
    }
    if (result == AttackResult::BLOCK) {
        increment_full_block();
        pchar->gain_rage(pchar->rage_gained_from_dd(pchar->get_avg_mh_damage()));
        return;
    }

    if (pchar->get_recklessness_buff()->is_active())
        result = AttackResult::CRITICAL;

    float damage_dealt = pchar->get_random_non_normalized_oh_dmg() * talent_ranks[rank_talent];

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
        pchar->melee_oh_white_critical_effect();
        // TODO: Save statistics for resource gains
        add_crit_dmg(round(damage_dealt));
        pchar->gain_rage(rage_gained);
        return;
    }
    if (result == AttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(oh_wpn_skill));
        const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
        pchar->melee_oh_white_hit_effect();
        // TODO: Save statistics for resource gains
        add_glancing_dmg(damage_dealt);
        pchar->gain_rage(rage_gained);
        return;
    }

    pchar->melee_oh_white_hit_effect();
    damage_dealt = round(damage_dealt);
    const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
    // TODO: Save statistics for resource gains
    add_hit_dmg(damage_dealt);
    pchar->gain_rage(rage_gained);
}
