
#include "OffhandAttackWarrior.h"
#include "Warrior.h"
#include "DeepWounds.h"

OffhandAttackWarrior::OffhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll) :
    OffhandAttack(engine,
                  pchar,
                  roll)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625};
}

void OffhandAttackWarrior::extra_attack() {
    pchar->gain_rage(calculate_damage());
}

int OffhandAttackWarrior::spell_effect(const int) {
    complete_swing();
    return calculate_damage();
}

int OffhandAttackWarrior::calculate_damage() {
    const int oh_wpn_skill = pchar->get_oh_wpn_skill();
    const int result = roll->get_melee_hit_result(oh_wpn_skill);

    if (result == AttackResult::MISS) {
        increment_miss();
        return 0;
    }
    // TODO: Apply Overpower
    if (result == AttackResult::DODGE) {
        increment_dodge();
        return pchar->rage_gained_from_dd(pchar->get_avg_mh_damage());
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        return pchar->rage_gained_from_dd(pchar->get_avg_mh_damage());
    }
    if (result == AttackResult::BLOCK) {
        increment_full_block();
        return pchar->rage_gained_from_dd(pchar->get_avg_mh_damage());
    }

    float damage_dealt = pchar->get_random_non_normalized_oh_dmg() * talent_ranks[rank_talent];

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
        pchar->melee_oh_white_critical_effect();
        // TODO: Save statistics for resource gains
        add_crit_dmg(round(damage_dealt));
        return rage_gained;
    }
    if (result == AttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(oh_wpn_skill));
        const int rage_gained = pchar->rage_gained_from_dd(round(damage_dealt));
        pchar->melee_oh_white_hit_effect();
        // TODO: Save statistics for resource gains
        add_glancing_dmg(damage_dealt);
        return rage_gained;
    }

    pchar->melee_oh_white_hit_effect();
    damage_dealt = round(damage_dealt);
    const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
    // TODO: Save statistics for resource gains
    add_hit_dmg(damage_dealt);
    return rage_gained;
}
