
#include "Execute.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

Execute::Execute(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Execute", engine, pchar, roll, 0, 15)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    spell_ranks = {QPair<int, int>(125, 3),
                   QPair<int, int>(200, 6),
                   QPair<int, int>(325, 9),
                   QPair<int, int>(450, 12),
                   QPair<int, int>(600, 15)};
    // TODO: Remove hardcoded assumption of rank 5 Execute.
    rank_spell = 4;
    initial_dmg = spell_ranks[rank_spell].first;
    dmg_per_rage_converted = spell_ranks[rank_spell].second;

    talent_ranks = {15, 13, 10};
}

void Execute::spell_effect() {
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    add_gcd_event();

    // TODO: Check Execute rage loss on miss/dodge/parry
    if (result == AttackResult::MISS) {
        increment_miss();
        pchar->lose_rage(resource_cost);
        return;
    }
    // TODO: Apply Overpower
    if (result == AttackResult::DODGE) {
        increment_dodge();
        pchar->lose_rage(round(resource_cost * 0.25));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        pchar->lose_rage(round(resource_cost * 0.25));
        return;
    }

    float damage_dealt = initial_dmg + (pchar->get_curr_rage() - resource_cost) * dmg_per_rage_converted;
    damage_dealt *= pchar->get_total_phys_dmg_mod();

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * pchar->get_ability_crit_dmg_mod());
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(damage_dealt);
    }
    else if (result == AttackResult::HIT) {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }

    pchar->lose_rage(pchar->get_curr_rage());
}

void Execute::increase_effect_via_talent() {
    ++rank_talent;
    // TODO: Assert max rank?
    resource_cost = talent_ranks[rank_talent];
}

void Execute::decrease_effect_via_talent() {
    --rank_talent;
    assert(rank_talent >= 0);
    resource_cost = talent_ranks[rank_talent];
}
