
#include "ElixirOfTheMongoose.h"
#include "Character.h"
#include "CharacterStats.h"

ElixirOfTheMongoose::ElixirOfTheMongoose(Character* pchar):
    ExternalBuff(pchar, "Elixir of the Mongoose", 300, 1, "Assets/buffs/Inv_potion_32.png",
                 "+25 Agility, +%2 Critical Strike", QVersionNumber::fromString("1.0.0"))
{}

void ElixirOfTheMongoose::buff_effect_when_applied() {
    pchar->get_stats()->increase_agility(25);
    pchar->get_stats()->increase_crit(0.02);
}

void ElixirOfTheMongoose::buff_effect_when_removed() {
    pchar->get_stats()->decrease_agility(25);
    pchar->get_stats()->decrease_crit(0.02);
}
