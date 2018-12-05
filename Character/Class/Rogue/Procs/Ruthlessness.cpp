#include "Ruthlessness.h"

#include "ProcInfo.h"
#include "Rogue.h"

Ruthlessness::Ruthlessness(Character* pchar) :
    Proc("Ruthlessness", "Assets/ability/Ability_druid_disembowel.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Ruthlessness", 3, DisabledAtZero::Yes)}),
    rogue(dynamic_cast<Rogue*>(pchar))
{
    this->enabled = false;
    this->talent_ranks = {0, 2000, 4000, 6000};
    proc_range = talent_ranks[0];
}

Ruthlessness::~Ruthlessness() = default;

void Ruthlessness::proc_effect() {
    rogue->gain_combo_points(1);
}

void Ruthlessness::increase_talent_rank_effect(const int curr, const QString&) {
    proc_range = talent_ranks[curr];
}

void Ruthlessness::decrease_talent_rank_effect(const int curr, const QString&) {
    proc_range = talent_ranks[curr];
}
