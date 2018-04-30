
#include "WindfuryTotemAttack.h"
#include "Character.h"

WindfuryTotemAttack::WindfuryTotemAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Proc("Windfury Totem Attack", 0.0, 0, false, QVector<Proc*>(), engine, pchar, roll)
{
}

WindfuryTotemAttack::~WindfuryTotemAttack() {
}

void WindfuryTotemAttack::proc_effect() {
    // TODO: Check if Windfury Totem extra attacks can glance.
    pchar->increase_melee_ap(rank_spells[rank_spell]);
    pchar->run_extra_attack();
    pchar->decrease_melee_ap(rank_spells[rank_spell]);
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
