
#include "Overpower.h"
#include "Warrior.h"
#include "OverpowerBuff.h"
#include "CharacterStats.h"

Overpower::Overpower(Character* pchar) :
    Spell("Overpower", "Assets/warrior/arms/tier3/Inv_sword_05.png", pchar, true, 5.0, 5),
    TalentRequirer(2, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->talent_ranks = {0.0, 0.25, 0.5};
    crit_mod = talent_ranks[curr_talent_rank];
}

bool Overpower::is_ready_spell_specific() const {
    return warr->in_battle_stance() && warr->get_overpower_buff()->is_active();
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
    warr->lose_rage(resource_cost);

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_normalized_mh_dmg() + 35);

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= warr->get_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)));
    }
    else if (result == AttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)));
    }
}

void Overpower::increase_talent_rank_effect(const QString&) {
    crit_mod = talent_ranks[curr_talent_rank];
}

void Overpower::decrease_talent_rank_effect(const QString&) {
    crit_mod = talent_ranks[curr_talent_rank];
}
