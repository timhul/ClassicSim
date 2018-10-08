
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "StatisticsResource.h"
#include "ProcInfo.h"

UnbridledWrath::UnbridledWrath(Character* pchar) :
    Proc("Unbridled Wrath", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing,
                                    ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing}),
         pchar),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->talent_ranks = {0, 8, 16, 24, 32, 40};
}

UnbridledWrath::~UnbridledWrath() = default;

void UnbridledWrath::proc_effect() {
    unsigned rage = warr->get_curr_rage();
    warr->gain_rage(1);

    if (warr->get_curr_rage() != rage)
        statistics_resource->add_resource_gain(1);
}

void UnbridledWrath::increase_effect_via_talent() {
    ++rank_talent;
    if (rank_talent == 1)
        this->enable_proc();

    proc_range = talent_ranks[rank_talent] * 100;
}

void UnbridledWrath::decrease_effect_via_talent() {
    --rank_talent;
    if (rank_talent == 0)
        this->disable_proc();

    assert(rank_talent >= 0);
    proc_range = talent_ranks[rank_talent] * 100;
}
