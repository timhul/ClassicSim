#include "DragonbreathChili.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Random.h"
#include "StatisticsSpell.h"
#include "Utils/Check.h"

DragonbreathChili::DragonbreathChili(Character* pchar) :
    Proc("Dragonbreath Chili", "Assets/spell/Spell_fire_incinerate.png", 0.075, 0, {},
         {ProcInfo::MainhandSwing, ProcInfo::MainhandSwing, ProcInfo::OffhandSwing},
         pchar),
    damage_roll(new Random(50, 60))
{
    enabled = false;
}

DragonbreathChili::~DragonbreathChili() {
    delete damage_roll;
}

void DragonbreathChili::proc_effect() {
    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Fire, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    const unsigned damage_dealt = damage_roll->get_roll() + static_cast<unsigned>(round(pchar->get_stats()->get_spell_damage(MagicSchool::Fire) * spell_dmg_coefficient));

    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);
    const double damage_mod =  pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Fire);
        add_crit_dmg(static_cast<int>(round(damage_dealt * damage_mod * pchar->get_stats()->get_spell_crit_dmg_mod() * resist_mod)), resource_cost, 0);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Fire);
        add_hit_dmg(static_cast<int>(round(damage_dealt * damage_mod * resist_mod)), resource_cost, 0);
    }
}

void DragonbreathChili::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_spell = pchar->get_statistics()->get_spell_statistics(name, icon, 1);
}
