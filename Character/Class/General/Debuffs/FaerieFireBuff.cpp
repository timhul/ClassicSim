
#include "FaerieFireBuff.h"
#include "Character.h"
#include "Target.h"

FaerieFireBuff::FaerieFireBuff(Character* pchar):
    ExternalBuff(pchar, "Faerie Fire", BuffDuration::PERMANENT, 0,
                 "Assets/buffs/Spell_nature_faeriefire.png",
                 "Reduces target armor by 505.", QVersionNumber::fromString("1.0.0"))
{}

void FaerieFireBuff::buff_effect_when_applied() {
    pchar->get_target()->decrease_armor(505);
}

void FaerieFireBuff::buff_effect_when_removed() {
    pchar->get_target()->increase_armor(505);
}
