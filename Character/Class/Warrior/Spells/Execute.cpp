#include "Execute.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "DeepWounds.h"
#include "Engine.h"
#include "Flurry.h"
#include "OverpowerBuff.h"
#include "SimSettings.h"
#include "Warrior.h"

Execute::Execute(Character* pchar) :
    Spell("Execute", "Assets/items/Inv_sword_48.png", pchar, RestrictedByGcd::Yes, 0, ResourceType::Rage, 15),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Execute", 2, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    execute_threshold(0.2)
{
    spell_ranks = {QPair<int, int>(125, 3),
                   QPair<int, int>(200, 6),
                   QPair<int, int>(325, 9),
                   QPair<int, int>(450, 12),
                   QPair<int, int>(600, 15)};
    spell_rank = 4;
    initial_dmg = spell_ranks[spell_rank].first;
    dmg_per_rage_converted = spell_ranks[spell_rank].second;

    talent_ranks = {15, 13, 10};
}


bool Execute::is_ready_spell_specific() const {
    if (warr->in_defensive_stance())
        return false;

    int combat_length = warr->get_sim_settings()->get_combat_length();
    double time_remaining = combat_length - warr->get_engine()->get_current_priority();
    return time_remaining / combat_length < execute_threshold;
}

void Execute::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    // CSIM-70: Investigate Execute rage loss on miss/dodge/parry
    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        warr->lose_rage(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = initial_dmg + (warr->get_resource_level(resource_type) - resource_cost) * dmg_per_rage_converted;
    damage_dealt = damage_after_modifiers(damage_dealt);

    if (result == PhysicalAttackResult::CRITICAL) {
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * warr->get_ability_crit_dmg_mod())), int(warr->get_resource_level(resource_type)), pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), int(warr->get_resource_level(resource_type)), pchar->global_cooldown());
    }

    warr->lose_rage(warr->get_resource_level(resource_type));
}

void Execute::increase_talent_rank_effect(const QString&, const int curr) {
    resource_cost = talent_ranks[curr];
}

void Execute::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = talent_ranks[curr];
}

void Execute::set_execute_threshold(const double execute_threshold) {
    assert(execute_threshold > -0.0001 && execute_threshold < 1.0001),
    this->execute_threshold = execute_threshold;
}

void Execute::reset_execute_threshold() {
    this->execute_threshold = 0.2;
}
