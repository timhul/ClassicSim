
#include "ShadowBoltAttack.h"
#include "Character.h"
#include "CharacterStats.h"
#include "Random.h"

ShadowBoltAttack::ShadowBoltAttack(Character* pchar, const QString &name, const unsigned min, const unsigned max) :
    Spell(name, pchar, false, 0, 0),
    min(min), max(max),
    random(new Random(min, max))
{}

ShadowBoltAttack::~ShadowBoltAttack() {
    delete random;
}

void ShadowBoltAttack::spell_effect() {
    // CSIM-60: Add spell attack table and use it here
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill(),
                                                      pchar->get_stats()->get_mh_crit_chance());

    unsigned damage_dealt = random->get_roll();

    if (result == AttackResult::CRITICAL) {
        pchar->spell_critical_effect();
        add_crit_dmg(static_cast<int>(damage_dealt * pchar->get_spell_crit_dmg_mod()));
    }
    else if (result == AttackResult::HIT) {
        pchar->spell_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)));
    }
}
