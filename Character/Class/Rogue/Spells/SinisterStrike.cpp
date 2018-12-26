#include "SinisterStrike.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Rogue.h"
#include "SealFate.h"
#include "Weapon.h"

SinisterStrike::SinisterStrike(Character* pchar) :
    Spell("Sinister Strike", "Assets/spell/Spell_shadow_ritualofsacrifice.png", pchar, RestrictedByGcd::Yes, 0.0, ResourceType::Energy, 45),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Aggression", 3, DisabledAtZero::No),
                   new TalentRequirerInfo("Improved Sinister Strike", 2, DisabledAtZero::No),
                   new TalentRequirerInfo("Lethality", 5, DisabledAtZero::No)
                   }),
    rogue(dynamic_cast<Rogue*>(pchar)),
    aggression(1.0),
    lethality(1.0)
{
    imp_ss_ranks = {45, 42, 40};
    aggression_ranks = {1.0, 1.02, 1.04, 1.06};
    lethality_ranks = {1.0, 1.06, 1.12, 1.18, 1.24, 1.30};
}

void SinisterStrike::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double base_dmg = rogue->get_random_normalized_mh_dmg() + 68.0;
    double damage_dealt = damage_after_modifiers(base_dmg * aggression);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * rogue->get_ability_crit_dmg_mod() * lethality);
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());

        if (rogue->get_seal_fate()->is_enabled()) {
            rogue->get_seal_fate()->set_current_proc_source(ProcInfo::Source::MainhandSpell);
            rogue->get_seal_fate()->perform();
        }
    }
    else if (result == PhysicalAttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    rogue->lose_energy(static_cast<unsigned>(resource_cost));
    rogue->gain_combo_points(1);
}

void SinisterStrike::increase_talent_rank_effect(const int curr, const QString& talent_name) {
    if (talent_name == "Improved Sinister Strike")
        resource_cost = imp_ss_ranks[curr];
    else if (talent_name == "Aggression")
        aggression = aggression_ranks[curr];
    else if (talent_name == "Lethality")
        lethality = lethality_ranks[curr];
}

void SinisterStrike::decrease_talent_rank_effect(const int curr, const QString& talent_name) {
    if (talent_name == "Improved Sinister Strike")
        resource_cost = imp_ss_ranks[curr];
    else if (talent_name == "Aggression")
        aggression = aggression_ranks[curr];
    else if (talent_name == "Lethality")
        lethality = lethality_ranks[curr];
}
