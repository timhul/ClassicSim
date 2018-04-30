
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
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    float damage_dealt = pchar->get_stats()->get_melee_ap() * 0.45 * pchar->get_stats()->get_total_phys_dmg_mod();

    if (result->is_critical()) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_mh_critical_effect();
        add_success_stats("Critical", round(damage_dealt));
    }
    else if (result->is_hit())
        add_success_stats("Hit", round(damage_dealt));

    add_spell_cd_event();
    add_gcd_event();

    return resource_cost;
}
