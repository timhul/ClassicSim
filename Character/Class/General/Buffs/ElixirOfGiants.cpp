
#include "ElixirOfGiants.h"
#include "Character.h"
#include "CharacterStats.h"

ElixirOfGiants::ElixirOfGiants(Character* pchar):
    ExternalBuff(pchar, "Elixir of Giants", BuffDuration::PERMANENT, 1,
                 "Assets/buffs/Inv_potion_61.png",
                 "+25 Strength", QVersionNumber::fromString("1.0.0"))
{
    this->enabled = true;
}

void ElixirOfGiants::buff_effect_when_applied() {
    pchar->get_stats()->increase_strength(25);
}

void ElixirOfGiants::buff_effect_when_removed() {
    pchar->get_stats()->decrease_strength(25);
}
