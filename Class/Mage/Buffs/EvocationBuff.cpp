#include "EvocationBuff.h"

#include "Mage.h"
#include "Mana.h"
#include "Utils/Check.h"

EvocationBuff::EvocationBuff(Mage* mage):
    SelfBuff(mage, "Evocation", "Assets/spell/Spell_nature_purge.png", 8, 0),
    mana(static_cast<Mana*>(mage->get_resource()))
{
    check((mana != nullptr), "EvocationBuff:: Mana nullptr");
}

void EvocationBuff::buff_effect_when_applied() {
    mana->ignore_5sr = true;
    mana->bonus_regen_modifier += 15.0;
}

void EvocationBuff::buff_effect_when_removed() {
    mana->ignore_5sr = false;
    mana->bonus_regen_modifier -= 15.0;
}
