
#include "ElixirOfBruteForce.h"
#include "Character.h"
#include "CharacterStats.h"

ElixirOfBruteForce::ElixirOfBruteForce(Character* pchar):
    ExternalBuff(pchar, "Elixir of Brute Force", BuffDuration::PERMANENT, 1,
                 "Assets/buffs/Inv_potion_40.png",
                 "+18 Strength and Stamina", QVersionNumber::fromString("1.0.0"))
{
    this->enabled = true;
}

void ElixirOfBruteForce::buff_effect_when_applied() {
    pchar->get_stats()->increase_strength(18);
    pchar->get_stats()->increase_stamina(18);
}

void ElixirOfBruteForce::buff_effect_when_removed() {
    pchar->get_stats()->decrease_strength(18);
    pchar->get_stats()->decrease_stamina(18);
}
