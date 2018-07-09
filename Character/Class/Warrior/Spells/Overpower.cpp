
#include "Overpower.h"
#include "Warrior.h"
#include "OverpowerBuff.h"

Overpower::Overpower(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Overpower", engine, pchar, roll, true, 5.0, 5)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    this->talent_ranks = {0.0, 0.25, 0.5};
}

bool Overpower::is_ready_spell_specific() const {
    return pchar->in_battle_stance() && pchar->get_overpower_buff()->is_active();
}

void Overpower::spell_effect() {
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill(),
                                                      talent_ranks[rank_talent],
                                                      false,
                                                      false,
                                                      false,
                                                      true);

    pchar->get_overpower_buff()->cancel_buff();
    add_gcd_event();
    add_spell_cd_event();
    pchar->lose_rage(resource_cost);

    if (result == AttackResult::MISS) {
        increment_miss();
        return;
    }

    float damage_dealt = damage_after_modifiers(pchar->get_random_normalized_mh_dmg() + 35);

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= pchar->get_ability_crit_dmg_mod();
        pchar->melee_mh_yellow_critical_effect();
        add_crit_dmg(round(damage_dealt));
    }
    else if (result == AttackResult::HIT) {
        pchar->melee_mh_yellow_hit_effect();
        add_hit_dmg(round(damage_dealt));
    }
}
