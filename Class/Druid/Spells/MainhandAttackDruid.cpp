#include "MainhandAttackDruid.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "Equipment.h"
#include "Flurry.h"
#include "RecklessnessBuff.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"
#include "Weapon.h"

MainhandAttackDruid::MainhandAttackDruid(Druid* pchar) : MainhandAttack(pchar), druid(pchar) {}

void MainhandAttackDruid::calculate_damage() {
    const unsigned mh_wpn_skill = get_weapon_skill();
    const int result = roll->get_melee_hit_result(mh_wpn_skill, pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        if (druid->get_current_form() == DruidForm::Bear)
            pchar->add_player_reaction_event();
        return;
    }

    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        if (druid->get_current_form() == DruidForm::Bear)
            gain_rage(druid->get_avg_mh_damage());
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        if (druid->get_current_form() == DruidForm::Bear)
            gain_rage(druid->get_avg_mh_damage());
        return;
    }
    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL) {
        increment_full_block();
        if (druid->get_current_form() == DruidForm::Bear)
            gain_rage(druid->get_avg_mh_damage());
        return;
    }

    double damage_dealt = damage_after_modifiers(druid->get_random_non_normalized_mh_dmg());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        add_crit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        druid->melee_mh_white_critical_effect();

        if (druid->get_current_form() == DruidForm::Bear)
            gain_rage(damage_dealt);

        return;
    }

    druid->melee_mh_white_hit_effect();

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(mh_wpn_skill));
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);

        if (druid->get_current_form() == DruidForm::Bear)
            gain_rage(damage_dealt);

        return;
    }

    damage_dealt = round(damage_dealt);
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);

    if (druid->get_current_form() == DruidForm::Bear)
        gain_rage(damage_dealt);
}

void MainhandAttackDruid::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_mainhand()->get_value("icon");
    this->cooldown->base = pchar->get_stats()->get_mh_wpn_speed();
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);

    reset();
}

void MainhandAttackDruid::gain_rage(const double damage_dealt) {
    const unsigned rage_gained = druid->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
    const unsigned before = druid->get_resource_level(ResourceType::Rage);

    druid->gain_rage(rage_gained);

    const unsigned gain_after_cap = druid->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}

unsigned MainhandAttackDruid::get_weapon_skill() const {
    switch (druid->get_current_form()) {
    case DruidForm::Bear:
    case DruidForm::Cat:
        return pchar->get_clvl() * 5;
    case DruidForm::Caster:
    case DruidForm::Moonkin:
        return pchar->get_stats()->get_mh_wpn_skill();
    }

    check(false, "Reached end of switch in MainhandAttackDruid::get_weapon_skill()");
    return pchar->get_clvl() * 5;
}
