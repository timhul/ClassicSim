
#include "MainhandAttackWarrior.h"
#include "Warrior.h"
#include "Flurry.h"
#include "Equipment.h"
#include "DeepWounds.h"

MainhandAttackWarrior::MainhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll) :
    MainhandAttack(engine,
                   pchar,
                   roll)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

void MainhandAttackWarrior::extra_attack() {
    pchar->gain_rage(calculate_damage());
}

int MainhandAttackWarrior::spell_effect(const int) {
    complete_swing();
    return calculate_damage();
}

int MainhandAttackWarrior::calculate_damage() {
    // TODO: complete_swing() ? OffhandAttackWarrior has it, do not remember difference.

    const int mh_wpn_skill = pchar->get_mh_wpn_skill();
    AttackResult* result = roll->get_melee_hit_result(mh_wpn_skill);

    if (result->is_miss()) {
        increment_miss();
        return 0;
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        increment_dodge();
        return pchar->rage_gained_from_dd(pchar->get_avg_mh_damage());
    }
    if (result->is_parry()) {
        increment_parry();
        return pchar->rage_gained_from_dd(pchar->get_avg_mh_damage());
    }
    if (result->is_block()) {
        increment_full_block();
        return pchar->rage_gained_from_dd(pchar->get_avg_mh_damage());
    }

    float damage_dealt = pchar->get_random_non_normalized_mh_dmg();

    if (result->is_critical()) {
        damage_dealt = round(damage_dealt * 2);
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        pchar->melee_mh_critical_effect();
        add_crit_dmg(damage_dealt);
        // TODO: Save statistics for resource gains
        return rage_gained;
    }
    if (result->is_glancing()) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        pchar->melee_mh_hit_effect();
        add_glancing_dmg(damage_dealt);
        // TODO: Save statistics for resource gains
        return rage_gained;
    }

    damage_dealt = round(damage_dealt);
    const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
    pchar->melee_mh_hit_effect();
    add_hit_dmg(damage_dealt);
    // TODO: Save statistics for resource gains
    return rage_gained;
}
