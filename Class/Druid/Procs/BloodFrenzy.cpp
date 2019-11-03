#include "BloodFrenzy.h"

#include "Druid.h"
#include "ProcInfo.h"

BloodFrenzy::BloodFrenzy(Druid* druid) :
    Proc("Blood Frenzy", "Assets/ability/Ability_ghoulfrenzy.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         druid),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Blood Frenzy", 2, DisabledAtZero::Yes)}),
    druid(druid),
    talent_ranks({0, 5000, 10000})
{
    this->enabled = false;
    proc_range = talent_ranks[0];
}

void BloodFrenzy::proc_effect() {
    druid->gain_combo_points(1);
}

void BloodFrenzy::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void BloodFrenzy::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}
