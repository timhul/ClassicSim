
#include "AnnihilatorBuff.h"
#include "Character.h"
#include "Target.h"

AnnihilatorBuff::AnnihilatorBuff(Character* pchar):
    ExternalBuff(pchar, "Annihilator Proc", BuffDuration::PERMANENT, 0,
                 "Assets/items/Inv_axe_12.png",
                 "Reduces target armor by 600.", QVersionNumber::fromString("1.0.0"))
{
    this->enabled = true;
}

void AnnihilatorBuff::buff_effect_when_applied() {
    pchar->get_target()->decrease_armor(600);
}

void AnnihilatorBuff::buff_effect_when_removed() {
    pchar->get_target()->increase_armor(600);
}
