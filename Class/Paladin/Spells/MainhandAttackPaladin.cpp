#include "MainhandAttackPaladin.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "PaladinSpells.h"

MainhandAttackPaladin::MainhandAttackPaladin(Paladin* paladin, PaladinSpells* paladin_spells) :
    MainhandAttack(paladin),
    paladin(paladin),
    paladin_spells(paladin_spells)
{}

void MainhandAttackPaladin::apply_seal_of_the_crusader_penalty() {
    this->sotc_penalty = 1 / 1.4;
}

void MainhandAttackPaladin::remove_seal_of_the_crusader_penalty() {
    this->sotc_penalty = 1.0;
}

void MainhandAttackPaladin::calculate_damage() {
    pchar->add_player_reaction_event();

    const unsigned mh_wpn_skill = pchar->get_mh_wpn_skill();
    const int result = roll->get_melee_hit_result(mh_wpn_skill, pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS)
        return increment_miss();
    if (result == PhysicalAttackResult::DODGE)
        return increment_dodge();
    if (result == PhysicalAttackResult::PARRY)
        return increment_parry();
    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL)
        return increment_full_block();

    PaladinSeal* seal = paladin_spells->get_judged_seal();
    if (seal != nullptr)
        seal->refresh_seal();

    double damage_dealt = damage_after_modifiers(paladin->get_random_non_normalized_mh_dmg()) * sotc_penalty;

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        add_crit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);

        paladin->get_vengeance()->apply_buff();
        paladin->melee_mh_white_critical_effect();
        return;
    }

    paladin->melee_mh_white_hit_effect();

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        return;
    }

    damage_dealt = round(damage_dealt);
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
}
