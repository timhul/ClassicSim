
#include "FieryWeaponAttack.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

FieryWeaponAttack::FieryWeaponAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Fiery Weapon", engine, pchar, roll, 0, 0)
{}

int FieryWeaponAttack::spell_effect(const int) {
    // TODO: Add spell table, since Fiery Weapon deals fire damage.
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    float damage_dealt = 40;
    // TODO: Apply +damage bonus at ratio (unknown ratio atm).
    damage_dealt *= 1;

    if (result->is_critical()) {
        // TODO: Remove assumption player has 50% spell crit damage (e.g. Ruin)
        damage_dealt = round(damage_dealt * 1.5);
        pchar->spell_critical_effect();
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit()) {
        pchar->spell_hit_effect();
        add_success_stats("Hit", round(damage_dealt));
    }

    return 0;
}
