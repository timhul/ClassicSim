
#include "WindfuryTotemAttack.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ProcInfo.h"

WindfuryTotemAttack::WindfuryTotemAttack(Character* pchar) :
    Proc("Windfury Totem Attack", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing}),
         pchar)
{}

WindfuryTotemAttack::~WindfuryTotemAttack() = default;

void WindfuryTotemAttack::proc_effect() {
    pchar->get_stats()->increase_melee_ap(rank_spells[spell_rank]);
    pchar->run_extra_mh_attack();
    pchar->get_stats()->decrease_melee_ap(rank_spells[spell_rank]);
}

void WindfuryTotemAttack::increase_spell_rank() {
    ++spell_rank;

    proc_range = 2000;
}

void WindfuryTotemAttack::decrease_spell_rank() {
    --spell_rank;

    if (spell_rank < 1)
        proc_range = 0;
}
