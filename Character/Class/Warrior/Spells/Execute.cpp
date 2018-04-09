
#include "Execute.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

Execute::Execute(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Execute", engine, pchar, roll, 0, 10)
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

    talent_ranks = {15, 12, 10};
}

int Execute::spell_effect(const int resource_level) {
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    float damage_dealt = initial_dmg + (resource_level - resource_cost) * dmg_per_rage_converted;
    damage_dealt *= pchar->get_total_phys_dmg_mod();

    if (result->is_critical()) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_critical_effect();
        add_success_stats("Critical", round(damage_dealt));
    }
    else if (result->is_hit())
        add_success_stats("Hit", round(damage_dealt));

    add_gcd_event();

    return resource_level;
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
