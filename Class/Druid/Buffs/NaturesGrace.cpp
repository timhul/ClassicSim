#include "NaturesGrace.h"

#include "Character.h"
#include "CharacterStats.h"

NaturesGrace::NaturesGrace(Character* pchar) :
    SelfBuff(pchar, "Nature's Grace", "Assets/spell/Spell_nature_naturesblessing.png", BuffDuration::PERMANENT, 1),
    TalentRequirer({new TalentRequirerInfo("Nature's Grace", 1, DisabledAtZero::Yes)}) {}

void NaturesGrace::buff_effect_when_applied() {
    pchar->get_stats()->increase_casting_speed_flat_reduction(500);
}

void NaturesGrace::buff_effect_when_removed() {
    pchar->get_stats()->decrease_casting_speed_flat_reduction(500);
}

void NaturesGrace::increase_talent_rank_effect(const QString&, const int) {}

void NaturesGrace::decrease_talent_rank_effect(const QString&, const int) {}
