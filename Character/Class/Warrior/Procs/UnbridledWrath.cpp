
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "StatisticsResource.h"
#include "ProcInfo.h"

UnbridledWrath::UnbridledWrath(Character* pchar) :
    Proc("Unbridled Wrath", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing,
                                    ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing}),
         pchar),
    TalentRequirer(5, DisabledAtZero::Yes),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
    this->talent_ranks = {0, 800, 1600, 2400, 3200, 4000};
    proc_range = talent_ranks[curr_talent_rank];
}

UnbridledWrath::~UnbridledWrath() = default;

void UnbridledWrath::proc_effect() {
    unsigned rage = warr->get_curr_rage();
    warr->gain_rage(1);

    if (warr->get_curr_rage() != rage)
        statistics_resource->add_resource_gain(1);
}

void UnbridledWrath::increase_talent_rank_effect(const QString&) {
    proc_range = talent_ranks[curr_talent_rank];
}

void UnbridledWrath::decrease_talent_rank_effect(const QString&) {
    proc_range = talent_ranks[curr_talent_rank];
}
