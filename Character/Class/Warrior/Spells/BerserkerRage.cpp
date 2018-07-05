
#include "BerserkerRage.h"
#include "Warrior.h"

BerserkerRage::BerserkerRage(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Berserker Rage", engine, pchar, roll, false, 30, 0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0, 5, 10};
}

void BerserkerRage::spell_effect() {
    add_spell_cd_event();

    pchar->gain_rage(talent_ranks[rank_talent]);
}
