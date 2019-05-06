#include "OffhandAttackWarrior.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Flurry.h"
#include "RecklessnessBuff.h"
#include "StatisticsResource.h"
#include "Warrior.h"
#include "Weapon.h"

OffhandAttackWarrior::OffhandAttackWarrior(Character* pchar) :
    OffhandAttack(pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Dual Wield Specialization", 5, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    talent_ranks = {0.5, 0.525, 0.55, 0.575, 0.6, 0.625};
    offhand_penalty = talent_ranks[0];
}

void OffhandAttackWarrior::increase_talent_rank_effect(const QString&, const int curr) {
    offhand_penalty = talent_ranks[curr];
}

void OffhandAttackWarrior::decrease_talent_rank_effect(const QString&, const int curr) {
    offhand_penalty = talent_ranks[curr];
}

void OffhandAttackWarrior::extra_attack() {
    calculate_damage();
}

void OffhandAttackWarrior::spell_effect() {
    complete_swing();
    const int result = calculate_damage();

    if (result == PhysicalAttackResult::HIT || result == PhysicalAttackResult::GLANCING)
        warr->get_flurry()->use_charge();
}

int OffhandAttackWarrior::calculate_damage() {
    const int oh_wpn_skill = warr->get_oh_wpn_skill();
    int result = roll->get_melee_hit_result(oh_wpn_skill, pchar->get_stats()->get_oh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return result;
    }

    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return result;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return result;
    }
    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL) {
        increment_full_block();
        warr->gain_rage(warr->rage_gained_from_dd(warr->get_avg_mh_damage()));
        return result;
    }

    if (warr->get_recklessness_buff()->is_active())
        result = PhysicalAttackResult::CRITICAL;

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_oh_dmg() * offhand_penalty);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        add_crit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        gain_rage(damage_dealt);

        warr->melee_oh_white_critical_effect();
        return result;
    }

    warr->melee_oh_white_hit_effect();

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(oh_wpn_skill));
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        gain_rage(damage_dealt);
        return result;
    }

    damage_dealt = round(damage_dealt);
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
    gain_rage(damage_dealt);
    return result;
}

void OffhandAttackWarrior::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_offhand() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_offhand()->get_value("icon");
    this->cooldown = pchar->get_stats()->get_oh_wpn_speed();
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);

    reset();
}

void OffhandAttackWarrior::gain_rage(const double damage_dealt) {
    const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
    const unsigned before = warr->get_resource_level(ResourceType::Rage);

    warr->gain_rage(rage_gained);

    const unsigned gain_after_cap = warr->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}
