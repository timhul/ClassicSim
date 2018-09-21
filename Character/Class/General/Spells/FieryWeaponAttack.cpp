
#include "FieryWeaponAttack.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

FieryWeaponAttack::FieryWeaponAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Fiery Weapon", engine, pchar, roll, false, 0, 0)
{}

void FieryWeaponAttack::spell_effect() {
    // TODO: Add spell table, since Fiery Weapon deals fire damage.
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    double damage_dealt = 40;
    // TODO: Apply +damage bonus at ratio (unknown ratio atm).
    damage_dealt *= 1;

    if (result == AttackResult::CRITICAL) {
        pchar->spell_critical_effect();
        // TODO: Remove assumption player has 50% spell crit damage (e.g. Ruin)
        add_crit_dmg(static_cast<int>(damage_dealt * 1.5));
    }
    else if (result == AttackResult::HIT) {
        pchar->spell_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)));
    }
}
