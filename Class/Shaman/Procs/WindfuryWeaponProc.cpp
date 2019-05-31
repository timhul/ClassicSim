#include "WindfuryWeaponProc.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "MainhandAttack.h"
#include "NoEffectBuff.h"
#include "ProcInfo.h"
#include "Shaman.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

WindfuryWeaponProc::WindfuryWeaponProc(Shaman* pchar, const int spell_rank) :
    Proc(QString("Windfury Weapon MH (rank %1)").arg(spell_rank), "Assets/spell/Spell_nature_cyclone.png", 0.2, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>(),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Elemental Weapons", 3, DisabledAtZero::No)})
{
    this->enabled = false;

    proc_sources = {
        ProcInfo::Source::MainhandSpell,
        ProcInfo::Source::MainhandSwing
    };

    switch (spell_rank) {
    case 1:
        base_bonus_melee_ap = 46;
        break;
    case 2:
        base_bonus_melee_ap = 119;
        break;
    case 3:
        base_bonus_melee_ap = 140;
        break;
    case 4:
        base_bonus_melee_ap = 333;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    bonus_melee_ap = base_bonus_melee_ap;
}

void WindfuryWeaponProc::proc_effect() {
    pchar->get_stats()->increase_melee_ap(bonus_melee_ap);

    pchar->get_spells()->get_mh_attack()->extra_attack();
    pchar->get_spells()->get_mh_attack()->extra_attack();

    pchar->get_stats()->decrease_melee_ap(bonus_melee_ap);
}

void WindfuryWeaponProc::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_spell = pchar->get_statistics()->get_spell_statistics(name, icon, spell_rank);
}

void WindfuryWeaponProc::increase_talent_rank_effect(const QString&, const int curr) {
    switch (curr) {
    case 0:
        bonus_melee_ap = base_bonus_melee_ap;
        break;
    case 1:
        bonus_melee_ap = static_cast<unsigned>(round(base_bonus_melee_ap * 1.13));
        break;
    case 2:
        bonus_melee_ap = static_cast<unsigned>(round(base_bonus_melee_ap * 1.27));
        break;
    case 3:
        bonus_melee_ap = static_cast<unsigned>(round(base_bonus_melee_ap * 1.40));
        break;
    default:
        check(false, QString("%1: Unsupported talent rank %2").arg(name).arg(curr).toStdString());
        break;
    }
}

void WindfuryWeaponProc::decrease_talent_rank_effect(const QString&, const int curr) {
    switch (curr) {
    case 0:
        bonus_melee_ap = base_bonus_melee_ap;
        break;
    case 1:
        bonus_melee_ap = static_cast<unsigned>(round(base_bonus_melee_ap * 1.13));
        break;
    case 2:
        bonus_melee_ap = static_cast<unsigned>(round(base_bonus_melee_ap * 1.27));
        break;
    case 3:
        bonus_melee_ap = static_cast<unsigned>(round(base_bonus_melee_ap * 1.40));
        break;
    default:
        check(false, QString("%1: Unsupported talent rank %2").arg(name).arg(curr).toStdString());
        break;
    }
}
