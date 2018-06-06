
#include "RallyingCryOfTheDragonslayer.h"
#include "Character.h"
#include "CharacterStats.h"

RallyingCryOfTheDragonslayer::RallyingCryOfTheDragonslayer(Character* pchar):
    ExternalBuff(pchar, "Rallying Cry of the Dragonslayer", BuffDuration::PERMANENT, 1,
                 "Assets/buffs/Inv_misc_head_dragon_01.png",
                 "+10% Spell crit, +5% melee/ranged crit, +140 attack power",
                 QVersionNumber::fromString("1.0.0"))
{}

void RallyingCryOfTheDragonslayer::buff_effect_when_applied() {
    // TODO: Add spell crit
    // pchar->get_stats()->increase_spell_crit(0.10);
    pchar->get_stats()->increase_crit(0.05);
    pchar->get_stats()->increase_melee_ap(140);
}

void RallyingCryOfTheDragonslayer::buff_effect_when_removed() {
    // TODO: Add spell crit
    // pchar->get_stats()->decrease_spell_crit(0.10);
    pchar->get_stats()->decrease_crit(0.05);
    pchar->get_stats()->decrease_melee_ap(140);
}
