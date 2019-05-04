#include "MainhandAttackWarrior.h"

#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "OverpowerBuff.h"
#include "RecklessnessBuff.h"
#include "StatisticsResource.h"
#include "Warrior.h"
#include "Weapon.h"

MainhandAttackWarrior::MainhandAttackWarrior(Character* pchar) :
    MainhandAttack(pchar),
    warr(dynamic_cast<Warrior*>(pchar))
{}

void MainhandAttackWarrior::extra_attack() {
    calculate_damage(false);
}

void MainhandAttackWarrior::spell_effect() {
    complete_swing();
    calculate_damage(true);
}

void MainhandAttackWarrior::calculate_damage(const bool run_procs) {
    const int mh_wpn_skill = warr->get_mh_wpn_skill();
    int result = roll->get_melee_hit_result(mh_wpn_skill, pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }

    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return;
    }
    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL) {
        increment_full_block();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return;
    }

    if (warr->get_recklessness_buff()->is_active())
        result = PhysicalAttackResult::CRITICAL;

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_mh_dmg());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        add_crit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        gain_rage(damage_dealt);
        warr->melee_mh_white_critical_effect(run_procs);
        return;
    }

    warr->melee_mh_white_hit_effect(run_procs);

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        gain_rage(damage_dealt);
        return;
    }

    damage_dealt = round(damage_dealt);
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
    gain_rage(damage_dealt);
}

void MainhandAttackWarrior::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_mainhand()->get_value("icon");
    this->cooldown = pchar->get_stats()->get_mh_wpn_speed();
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);

    reset();
}

void MainhandAttackWarrior::gain_rage(const double damage_dealt) {
    const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
    const unsigned before = warr->get_resource_level(ResourceType::Rage);

    warr->gain_rage(rage_gained);

    const unsigned gain_after_cap = warr->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}
