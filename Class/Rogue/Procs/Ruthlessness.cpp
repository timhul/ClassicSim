#include "Ruthlessness.h"

#include "ProcInfo.h"
#include "Rogue.h"

Ruthlessness::Ruthlessness(Rogue* rogue) :
    Proc("Ruthlessness", "Assets/ability/Ability_druid_disembowel.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         rogue),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Ruthlessness", 3, DisabledAtZero::Yes)}),
    rogue(rogue),
    talent_ranks({0, 2000, 4000, 6000})
{
    this->enabled = false;
    proc_range = talent_ranks[0];
}

void Ruthlessness::proc_effect() {
    rogue->gain_combo_points(1);
}

void Ruthlessness::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void Ruthlessness::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}
