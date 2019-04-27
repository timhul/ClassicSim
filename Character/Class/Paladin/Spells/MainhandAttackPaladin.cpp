#include "MainhandAttackPaladin.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "PaladinSpells.h"

MainhandAttackPaladin::MainhandAttackPaladin(Paladin* paladin) :
    MainhandAttack(paladin),
    paladin(paladin)
{}

void MainhandAttackPaladin::extra_attack() {
    calculate_damage(false);
}

void MainhandAttackPaladin::apply_seal_of_the_crusader_penalty() {
    this->sotc_penalty = 1 / 1.4;
}

void MainhandAttackPaladin::remove_seal_of_the_crusader_penalty() {
    this->sotc_penalty = 1.0;
}

void MainhandAttackPaladin::spell_effect() {
    complete_swing();
    calculate_damage(true);
}

void MainhandAttackPaladin::calculate_damage(const bool run_procs) {
    const int mh_wpn_skill = pchar->get_mh_wpn_skill();
    int result = roll->get_melee_hit_result(mh_wpn_skill, pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }

    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return;
    }
    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL) {
        increment_full_block();
        return;
    }

    PaladinSeal* seal = dynamic_cast<PaladinSpells*>(paladin->get_spells())->get_seal();
    if (seal != nullptr && seal->get_judge_debuff()->is_active())
        seal->get_judge_debuff()->apply_buff();

    double damage_dealt = damage_after_modifiers(paladin->get_random_non_normalized_mh_dmg()) * sotc_penalty;

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        add_crit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);

        paladin->melee_mh_white_critical_effect(run_procs);
        return;
    }

    paladin->melee_mh_white_hit_effect(run_procs);

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        return;
    }

    damage_dealt = round(damage_dealt);
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
}
