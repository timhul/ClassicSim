
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
        increment_miss();
    }
    // TODO: Apply Overpower
    else if (result->is_dodge()) {
        increment_dodge();
    }
    else if (result->is_parry()) {
        increment_parry();
    }

    float damage_dealt = pchar->get_random_normalized_mh_dmg();

    if (result->is_critical()) {
        damage_dealt = round(damage_dealt * pchar->get_ability_crit_dmg_mod());
        pchar->melee_mh_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result->is_hit()) {
        pchar->melee_mh_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }

    add_gcd_event();
    add_spell_cd_event();

    // TODO: Resource cost on failed hit should not be 100% of cost.
    return resource_cost;
}
