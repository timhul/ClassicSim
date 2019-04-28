#include "SealOfCommandProc.h"

#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "ItemNamespace.h"
#include "Paladin.h"
#include "PaladinSeal.h"
#include "PaladinSpells.h"
#include "ProcInfo.h"
#include "Utils/Check.h"

SealOfCommandProc::SealOfCommandProc(Character* pchar) :
    ProcPPM("Seal of Command (MH)", "Assets/ability/Ability_warrior_innerrage.png", EnchantSlot::MAINHAND,
            7.0, 0, QVector<Proc*>(),
            QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing,
                                       ProcInfo::Source::RangedSpell}),
            pchar),
    paladin(dynamic_cast<Paladin*>(pchar))
{
    this->enabled = false;
}

void SealOfCommandProc::proc_effect() {
    const int result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return;
    }

    PaladinSeal* seal = dynamic_cast<PaladinSpells*>(paladin->get_spells())->get_seal();
    if (seal != nullptr)
        seal->refresh_seal();

    double damage_dealt = (pchar->get_random_normalized_mh_dmg() + pchar->get_stats()->get_spell_damage(MagicSchool::Holy) * 0.2) * 0.7;
    damage_dealt *= pchar->get_stats()->get_spell_dmg_mod(MagicSchool::Holy);

    const int resist_result = roll->get_spell_resist_result(MagicSchool::Holy);
    double resist_mod = 1.0;
    switch (resist_result) {
    case MagicResistResult::NO_RESIST:
        break;
    case MagicResistResult::PARTIAL_RESIST_25:
        resist_mod = 0.75;
        break;
    case MagicResistResult::PARTIAL_RESIST_50:
        resist_mod = 0.5;
        break;
    case MagicResistResult::FULL_RESIST:
    case MagicResistResult::PARTIAL_RESIST_75:
        resist_mod = 0.25;
        break;
    default:
        check(false, "SealOfCommandProc::proc_effect reached end of switch");
    }

    damage_dealt *= resist_mod;

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= pchar->get_stats()->get_melee_ability_crit_dmg_mod();
        pchar->melee_mh_yellow_critical_effect();
        return add_crit_dmg(static_cast<int>(round(damage_dealt)), 0, pchar->global_cooldown());
    }
    pchar->melee_mh_yellow_hit_effect();
    return add_hit_dmg(static_cast<int>(round(damage_dealt)), 0, pchar->global_cooldown());
}

void SealOfCommandProc::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_spell = pchar->get_statistics()->get_spell_statistics(name, icon);
}
