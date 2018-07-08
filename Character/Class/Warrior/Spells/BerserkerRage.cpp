
#include "BerserkerRage.h"
#include "Warrior.h"

BerserkerRage::BerserkerRage(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Berserker Rage", engine, pchar, roll, false, 30, 0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0, 5, 10};
}

bool BerserkerRage::is_ready_spell_specific() const {
    return pchar->in_berserker_stance();
}

void BerserkerRage::spell_effect() {
    add_spell_cd_event();

    pchar->gain_rage(talent_ranks[rank_talent]);
}
