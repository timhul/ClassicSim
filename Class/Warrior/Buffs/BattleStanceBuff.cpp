#include "BattleStanceBuff.h"

#include "CharacterStats.h"
#include "Warrior.h"

BattleStanceBuff::BattleStanceBuff(Warrior* warrior):
    SelfBuff(warrior, "Battle Stance", NO_ICON, BuffDuration::PERMANENT, 1),
    warrior(warrior)
{
    this->hidden = true;
}

void BattleStanceBuff::buff_effect_when_applied() {
}

void BattleStanceBuff::buff_effect_when_removed() {
}
