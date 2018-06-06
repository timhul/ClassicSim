
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
}

int Bloodthirst::spell_effect(const int) {
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    add_spell_cd_event();
    add_gcd_event();

    if (result->is_miss()) {
        increment_miss();
        return resource_cost;
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        increment_dodge();
        return round(resource_cost * 0.25);
    }
    if (result->is_parry()) {
        increment_parry();
        return round(resource_cost * 0.25);
    }

    float damage_dealt = pchar->get_stats()->get_melee_ap() * 0.45 * pchar->get_stats()->get_total_phys_dmg_mod();

    if (result->is_critical()) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result->is_hit()) {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }

    return resource_cost;
}
