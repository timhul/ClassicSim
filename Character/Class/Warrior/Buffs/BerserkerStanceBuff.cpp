
#include "BerserkerStanceBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"

BerserkerStanceBuff::BerserkerStanceBuff(Character* pchar):
    Buff(pchar, "Berserker Stance", BuffDuration::PERMANENT, 1)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    this->hidden = true;
}

void BerserkerStanceBuff::buff_effect_when_applied() {
    // TODO: Add more damage taken
    pchar->get_stats()->increase_crit(0.03);
}

void BerserkerStanceBuff::buff_effect_when_removed() {
    // TODO: Add more damage taken
    pchar->get_stats()->decrease_crit(0.03);
}
