#include "EvocationBuff.h"

#include "Character.h"
#include "Mana.h"
#include "Utils/Check.h"

EvocationBuff::EvocationBuff(Character* pchar):
    SelfBuff(pchar, "Evocation", "Assets/spell/Spell_nature_purge.png", 8, 0),
    mana(dynamic_cast<class Mana*>(pchar->get_resource()))
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
