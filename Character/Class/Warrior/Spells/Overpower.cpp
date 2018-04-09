
#include "Overpower.h"
#include "Warrior.h"
#include "CooldownReady.h"
#include "Flurry.h"
#include "DeepWounds.h"

Overpower::Overpower(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Overpower", engine, pchar, roll, 5.0, 5)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0.0, 0.25, 0.5};
}

int Overpower::spell_effect(const int) {
    // TODO: Use special hit table where dodge and parry are not possible.
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill(), talent_ranks[rank_talent]);

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }

    int damage_dealt = pchar->get_mh_dmg() + 35;

    if (result->is_critical()) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_critical_effect();
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
