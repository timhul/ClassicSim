
#include "MainhandAttackWarrior.h"
#include "Warrior.h"
#include "DeepWounds.h"
#include "OverpowerBuff.h"
#include "RecklessnessBuff.h"

MainhandAttackWarrior::MainhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll) :
    MainhandAttack(engine, pchar, roll),
    warr(dynamic_cast<Warrior*>(pchar))
{}

void MainhandAttackWarrior::extra_attack() {
    calculate_damage();
}

void MainhandAttackWarrior::spell_effect() {
    complete_swing();
    calculate_damage();
}

void MainhandAttackWarrior::calculate_damage() {
    const int mh_wpn_skill = warr->get_mh_wpn_skill();
    int result = roll->get_melee_hit_result(mh_wpn_skill);

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }
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

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_mh_dmg());

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
        warr->melee_mh_white_critical_effect();
        add_crit_dmg(static_cast<int>(damage_dealt));
        // TODO: Save statistics for resource gains
        warr->gain_rage(rage_gained);
        return;
    }
    if (result == AttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
        warr->melee_mh_white_hit_effect();
        add_glancing_dmg(static_cast<int>(damage_dealt));
        // TODO: Save statistics for resource gains
        warr->gain_rage(rage_gained);
        return;
    }

    damage_dealt = round(damage_dealt);
    const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
    warr->melee_mh_white_hit_effect();
    add_hit_dmg(static_cast<int>(damage_dealt));
    // TODO: Save statistics for resource gains
    warr->gain_rage(rage_gained);
}
