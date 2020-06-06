#include "PrimalFury.h"

#include "Druid.h"
#include "ProcInfo.h"

PrimalFury::PrimalFury(Druid* druid) :
    Proc("Primal Fury",
         "Assets/ability/Ability_ghoulfrenzy.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         druid),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Primal Fury", 2, DisabledAtZero::Yes)}),
    druid(druid),
    talent_ranks({0, 5000, 10000}) {
    this->enabled = false;
    proc_range = talent_ranks[0];
}

void PrimalFury::proc_effect() {
    druid->gain_rage(5);
}

void PrimalFury::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void PrimalFury::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}
