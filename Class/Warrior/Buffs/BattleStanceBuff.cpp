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
    warrior->get_stats()->increase_total_threat_mod(-10);
}

void BattleStanceBuff::buff_effect_when_removed() {
    warrior->get_stats()->decrease_total_threat_mod(-10);
}
