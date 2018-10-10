
#include "Execute.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"
#include "OverpowerBuff.h"
#include "CharacterStats.h"

Execute::Execute(Character* pchar) :
    Spell("Execute", pchar, true, 0, 15),
    TalentRequirer(2, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar))
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

    // CSIM-69: Refactor this check into separate target mechanic.
    double time_remaining = 300 - warr->get_engine()->get_current_priority();
    return time_remaining / 300 < 0.2;
}

void Execute::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_gcd_event();

    // CSIM-70: Investigate Execute rage loss on miss/dodge/parry
    if (result == AttackResult::MISS) {
        increment_miss();
        warr->lose_rage(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = initial_dmg + (warr->get_curr_rage() - resource_cost) * dmg_per_rage_converted;
    damage_dealt = damage_after_modifiers(damage_dealt);

    if (result == AttackResult::CRITICAL) {
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * warr->get_ability_crit_dmg_mod())));
    }
    else if (result == AttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)));
    }

    warr->lose_rage(warr->get_curr_rage());
}

void Execute::increase_talent_rank_effect(const QString&) {
    resource_cost = talent_ranks[curr_talent_rank];
}

void Execute::decrease_talent_rank_effect(const QString&) {
    resource_cost = talent_ranks[curr_talent_rank];
}
