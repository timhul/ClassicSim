
#include "SunderArmorBuff.h"
#include "Character.h"
#include "Target.h"

SunderArmorBuff::SunderArmorBuff(Character* pchar):
    ExternalBuff(pchar, "Sunder Armor", BuffDuration::PERMANENT, 0,
                 "Assets/warrior/protection/tier4/Ability_warrior_sunder.png",
                 "Reduces target armor by 2250.", QVersionNumber::fromString("1.0.0"))
{
    this->enabled = true;
}

void SunderArmorBuff::buff_effect_when_applied() {
    pchar->get_target()->decrease_armor(2250);
}

void SunderArmorBuff::buff_effect_when_removed() {
    pchar->get_target()->increase_armor(2250);
}
