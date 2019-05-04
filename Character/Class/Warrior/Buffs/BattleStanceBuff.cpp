#include "BattleStanceBuff.h"

BattleStanceBuff::BattleStanceBuff(Character* pchar):
    Buff(pchar, "Battle Stance", NO_ICON, BuffDuration::PERMANENT, 1)
{
    this->hidden = true;
}

void BattleStanceBuff::buff_effect_when_applied() {
}

void BattleStanceBuff::buff_effect_when_removed() {
}
