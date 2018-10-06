
#include "DefensiveStanceBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"

DefensiveStanceBuff::DefensiveStanceBuff(Character* pchar):
    Buff(pchar, "Defensive Stance", BuffDuration::PERMANENT, 1),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->hidden = true;
}

void DefensiveStanceBuff::buff_effect_when_applied() {
    // CSIM-87: Defensive Stance
}

void DefensiveStanceBuff::buff_effect_when_removed() {
    // CSIM-87: Defensive Stance
}
