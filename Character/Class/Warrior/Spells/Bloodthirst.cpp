#include "Bloodthirst.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "DeepWounds.h"
#include "Flurry.h"
#include "OverpowerBuff.h"
#include "Warrior.h"

Bloodthirst::Bloodthirst(Character* pchar) :
    Spell("Bloodthirst", "Assets/spell/Spell_nature_bloodlust.png", pchar, RestrictedByGcd::Yes, 6.0, ResourceType::Rage, 30),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Bloodthirst", 1, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
}

void Bloodthirst::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_spell_cd_event();
    add_gcd_event();

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

    double damage_dealt = damage_after_modifiers(warr->get_stats()->get_melee_ap() * 0.45);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}

SpellStatus Bloodthirst::is_ready_spell_specific() const {
    if (warr->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void Bloodthirst::increase_talent_rank_effect(const QString&, const int) {
}

void Bloodthirst::decrease_talent_rank_effect(const QString&, const int) {
}
