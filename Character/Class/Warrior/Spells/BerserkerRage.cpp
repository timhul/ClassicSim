
#include "BerserkerRage.h"
#include "Warrior.h"

BerserkerRage::BerserkerRage(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Berserker Rage", engine, pchar, roll, 30, 0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0, 5, 10};
}

int BerserkerRage::spell_effect(const int) {
    add_spell_cd_event();

    return talent_ranks[rank_talent];
}
