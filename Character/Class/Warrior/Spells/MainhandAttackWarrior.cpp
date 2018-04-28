
#include "MainhandAttackWarrior.h"
#include "Warrior.h"
#include "Flurry.h"
#include "Equipment.h"
#include "DeepWounds.h"
#include "UnbridledWrath.h"

MainhandAttackWarrior::MainhandAttackWarrior(Engine* engine, Character* pchar, CombatRoll* roll) :
    MainhandAttack(engine,
                   pchar,
                   roll)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int MainhandAttackWarrior::spell_effect(const int) {
    complete_swing();
    // TODO: Check if Windfury is up, roll extra attacks.
    engine->get_statistics()->increment("MH White Total Attempts");

    const int mh_wpn_skill = pchar->get_mh_wpn_skill();
    AttackResult* result = roll->get_melee_hit_result(mh_wpn_skill);

    if (result->is_miss()) {
        add_fail_stats("Miss");
        return 0;
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
        return 0;
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
        return 0;
    }

    float damage_dealt = pchar->get_random_non_normalized_mh_dmg();
    int uw_proc = pchar->get_unbridled_wrath()->perform(0);

    if (result->is_critical()) {
        damage_dealt = round(damage_dealt * 2);
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        pchar->melee_critical_effect();
        add_success_stats("Critical", damage_dealt, rage_gained);
        return rage_gained + uw_proc;
    }
    else if (result->is_glancing()) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        pchar->get_flurry()->use_charge();
        add_success_stats("Glancing", damage_dealt, rage_gained);
        return rage_gained + uw_proc;
    }

    damage_dealt = round(damage_dealt);
    const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
    pchar->get_flurry()->use_charge();
    add_success_stats("Hit", damage_dealt, rage_gained);
    return rage_gained + uw_proc;
}
