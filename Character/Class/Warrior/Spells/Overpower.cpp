#include "Overpower.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "OverpowerBuff.h"
#include "Warrior.h"

Overpower::Overpower(Character* pchar) :
    Spell("Overpower", "Assets/items/Inv_sword_05.png", pchar, RestrictedByGcd::Yes, 5.0, ResourceType::Rage, 5),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Overpower", 2, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->talent_ranks = {0.0, 0.25, 0.5};
    crit_mod = talent_ranks[0];
}

bool Overpower::is_ready_spell_specific() const {
    return warr->in_battle_stance() && warr->get_overpower_buff()->is_active() && !warr->on_stance_cooldown();
}

void Overpower::spell_effect() {
    double total_crit = pchar->get_stats()->get_mh_crit_chance() + crit_mod;
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(),
                                                      total_crit,
                                                      false,
                                                      false,
                                                      false,
                                                      true);

    warr->get_overpower_buff()->cancel_buff();
    add_gcd_event();
    add_spell_cd_event();
    warr->lose_rage(static_cast<unsigned>(resource_cost));

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_normalized_mh_dmg() + 35);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
}

void Overpower::increase_talent_rank_effect(const QString&, const int curr) {
    crit_mod = talent_ranks[curr];
}

void Overpower::decrease_talent_rank_effect(const QString&, const int curr) {
    crit_mod = talent_ranks[curr];
}
