
#include "Whirlwind.h"
#include "CooldownReady.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

Whirlwind::Whirlwind(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Whirlwind", engine, pchar, roll, true, 10.0, 25)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

void Whirlwind::spell_effect() {
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    add_gcd_event();
    add_spell_cd_event();

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

    float damage_dealt = pchar->get_random_normalized_mh_dmg();

    if (result == AttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * pchar->get_ability_crit_dmg_mod());
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result == AttackResult::HIT) {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }

    pchar->lose_rage(resource_cost);
}
