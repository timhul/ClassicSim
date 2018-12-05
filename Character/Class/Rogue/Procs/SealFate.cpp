#include "SealFate.h"

#include "ProcInfo.h"
#include "Rogue.h"

SealFate::SealFate(Character* pchar) :
    Proc("Seal Fate", "Assets/spell/Spell_shadow_chilltouch.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Seal Fate", 5, DisabledAtZero::Yes)}),
    rogue(dynamic_cast<Rogue*>(pchar))
{
    this->enabled = false;
    this->talent_ranks = {0, 2000, 4000, 6000, 8000, 10000};
    proc_range = talent_ranks[0];
}

SealFate::~SealFate() = default;

void SealFate::proc_effect() {
    rogue->gain_combo_points(1);
}

void SealFate::increase_talent_rank_effect(const int curr, const QString&) {
    proc_range = talent_ranks[curr];
}

void SealFate::decrease_talent_rank_effect(const int curr, const QString&) {
    proc_range = talent_ranks[curr];
}
