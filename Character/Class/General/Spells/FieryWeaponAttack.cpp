
#include "FieryWeaponAttack.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

FieryWeaponAttack::FieryWeaponAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Fiery Weapon", engine, pchar, roll, false, 0, 0)
{}

void FieryWeaponAttack::spell_effect() {
    // CSIM-60: Add spell attack table and use it here
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    double damage_dealt = 40;
    // CSIM-64: Add +dmg as a stat and apply +damage bonus at ratio (unknown ratio atm).
    damage_dealt *= 1;

    if (result == AttackResult::CRITICAL) {
        pchar->spell_critical_effect();
        add_crit_dmg(static_cast<int>(damage_dealt * pchar->get_spell_crit_dmg_mod()));
    }
    else if (result == AttackResult::HIT) {
        pchar->spell_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)));
    }
}
