
#include "Whirlwind.h"
#include "CooldownReady.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

Whirlwind::Whirlwind(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Whirlwind", engine, pchar, roll, 10.0, 25)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int Whirlwind::spell_effect(const int) {
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

    int damage_dealt = std::max(1, pchar->get_random_mh_dmg());

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
