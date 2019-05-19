#include "WindfuryTotemAttack.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "MainhandAttack.h"
#include "ProcInfo.h"

WindfuryTotemAttack::WindfuryTotemAttack(Character* pchar) :
    Proc("Windfury Totem Attack", "Assets/spell/Spell_nature_windfury.png", 0.2, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing}),
         pchar)
{}

WindfuryTotemAttack::~WindfuryTotemAttack() = default;

void WindfuryTotemAttack::proc_effect() {
    pchar->get_stats()->increase_melee_ap(rank_spells[spell_rank]);
    pchar->get_spells()->get_mh_attack()->extra_attack();
    pchar->get_stats()->decrease_melee_ap(rank_spells[spell_rank]);
}
