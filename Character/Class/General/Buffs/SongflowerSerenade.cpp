
#include "SongflowerSerenade.h"
#include "Character.h"
#include "CharacterStats.h"

SongflowerSerenade::SongflowerSerenade(Character* pchar):
    ExternalBuff(pchar, "Songflower Serenade", BuffDuration::PERMANENT, 1,
                 "Assets/buffs/Spell_holy_mindvision.png",
                 "+5% Crit, +15 all attributes", QVersionNumber::fromString("1.0.0"))
{
    this->enabled = true;
}

void SongflowerSerenade::buff_effect_when_applied() {
    pchar->get_stats()->increase_crit(0.05);
    pchar->get_stats()->increase_agility(15);
    pchar->get_stats()->increase_strength(15);
    pchar->get_stats()->increase_stamina(15);
    pchar->get_stats()->increase_intellect(15);
    pchar->get_stats()->increase_spirit(15);
}

void SongflowerSerenade::buff_effect_when_removed() {
    pchar->get_stats()->decrease_crit(0.05);
    pchar->get_stats()->decrease_agility(15);
    pchar->get_stats()->decrease_strength(15);
    pchar->get_stats()->decrease_stamina(15);
    pchar->get_stats()->decrease_intellect(15);
    pchar->get_stats()->decrease_spirit(15);
}
