
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
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill(), talent_ranks[rank_talent]);

    add_gcd_event();
    add_spell_cd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        return resource_cost;
    }

    float damage_dealt = pchar->get_random_normalized_mh_dmg() + 35;
    damage_dealt *= pchar->get_total_phys_dmg_mod();

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result == AttackResult::HIT) {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }

    return resource_cost;
}
