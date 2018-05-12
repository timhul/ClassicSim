
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

    if (result->is_miss()) {
        increment_miss();
    }
    // TODO: Apply Overpower
    else if (result->is_dodge()) {
        increment_dodge();
    }
    else if (result->is_parry()) {
        increment_parry();
    }

    float damage_dealt = pchar->get_stats()->get_melee_ap() * 0.45 * pchar->get_stats()->get_total_phys_dmg_mod();

    if (result->is_critical()) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_mh_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result->is_hit())
        add_hit_dmg(round(damage_dealt));

    add_spell_cd_event();
    add_gcd_event();

    // TODO: Resource cost on failed hit should not be 100% of cost.
    return resource_cost;
}
