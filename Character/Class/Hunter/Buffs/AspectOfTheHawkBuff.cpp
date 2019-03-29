#include "AspectOfTheHawkBuff.h"

#include "Character.h"
#include "CharacterStats.h"

AspectOfTheHawkBuff::AspectOfTheHawkBuff(Character* pchar):
    Buff(pchar, "Aspect of the Hawk", "Assets/spell/Spell_nature_ravenform.png", BuffDuration::PERMANENT, 0)
{}

void AspectOfTheHawkBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_ap(120);
}

void AspectOfTheHawkBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_ap(120);
}
