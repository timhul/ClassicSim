
#include "Overpower.h"
#include "Warrior.h"
#include "CooldownReady.h"
#include "Flurry.h"
#include "DeepWounds.h"

Overpower::Overpower(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Overpower", engine, pchar, roll, 5.0, 5)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int Overpower::spell_effect(const int) {
    // TODO: Use special hit table where dodge and parry are not possible.
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }

    int damage_dealt = pchar->get_mh_dmg() + 35;

    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        pchar->critical_effect();
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}
