
#include "BerserkerRage.h"
#include "Warrior.h"

BerserkerRage::BerserkerRage(Character* pchar) :
    Spell("Berserker Rage", "Assets/warrior/fury/tier6/Spell_nature_ancestralguardian.png", pchar, RestrictedByGcd::No, 30, 0),
    TalentRequirer(2, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar))
{
    talent_ranks = {0, 5, 10};
    rage_gain = talent_ranks[curr_talent_rank];
}

bool BerserkerRage::is_ready_spell_specific() const {
    return warr->in_berserker_stance();
}

void BerserkerRage::spell_effect() {
    add_spell_cd_event();

    warr->gain_rage(rage_gain);
}

void BerserkerRage::increase_talent_rank_effect(const QString&) {
    rage_gain = talent_ranks[curr_talent_rank];
}

void BerserkerRage::decrease_talent_rank_effect(const QString&) {
    rage_gain = talent_ranks[curr_talent_rank];
}
