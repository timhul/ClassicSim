
#include "Bloodthirst.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "CooldownReady.h"
#include "Flurry.h"
#include "DeepWounds.h"

Bloodthirst::Bloodthirst(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Bloodthirst", engine, pchar, roll, 6.0, 30)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    this->enabled_by_talent = true;
}

void Bloodthirst::spell_effect() {
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    add_spell_cd_event();
    add_gcd_event();

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

    float damage_dealt = pchar->get_stats()->get_melee_ap() * 0.45 * pchar->get_stats()->get_total_phys_dmg_mod();

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result == AttackResult::HIT) {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }

    pchar->lose_rage(resource_cost);
}
