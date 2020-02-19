#include "SanctityAuraBuff.h"

#include "CharacterStats.h"
#include "Paladin.h"

SanctityAuraBuff::SanctityAuraBuff(Paladin* paladin) :
    PartyBuff(paladin, "Sanctity Aura", "Assets/spell/Spell_holy_mindvision.png", BuffDuration::PERMANENT, 0), paladin(paladin) {}

void SanctityAuraBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_magic_school_damage_mod(10, MagicSchool::Holy);
}

void SanctityAuraBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_magic_school_damage_mod(10, MagicSchool::Holy);
}
