
#include "WindfuryTotemAttack.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ProcInfo.h"

WindfuryTotemAttack::WindfuryTotemAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Proc("Windfury Totem Attack", 0.0, 0, false, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing}),
         engine, pchar, roll)
{}

WindfuryTotemAttack::~WindfuryTotemAttack() = default;

void WindfuryTotemAttack::proc_effect() {
    // TODO: Check if Windfury Totem extra attacks can glance.
    pchar->get_stats()->increase_melee_ap(rank_spells[rank_spell]);
    pchar->run_extra_mh_attack();
    pchar->get_stats()->decrease_melee_ap(rank_spells[rank_spell]);
}

void WindfuryTotemAttack::increase_spell_rank() {
    ++rank_spell;

    proc_range = 2000;
}

void WindfuryTotemAttack::decrease_spell_rank() {
    --rank_spell;

    if (rank_spell < 1)
        proc_range = 0;
}
