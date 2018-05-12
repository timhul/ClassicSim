
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "StatisticsResource.h"

UnbridledWrath::UnbridledWrath(Engine* engine, Character* pchar, CombatRoll* roll) :
    Proc("Unbridled Wrath", 0.0, 0, false, QVector<Proc*>(), engine, pchar, roll)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    this->talent_ranks = {0, 8, 16, 24, 32, 40};
}

UnbridledWrath::~UnbridledWrath() {
}

void UnbridledWrath::proc_effect() {
    int rage = pchar->get_curr_rage();
    pchar->gain_rage(1);

    if (pchar->get_curr_rage() != rage)
        statistics_resource->add_resource_gain(1);
}

void UnbridledWrath::increase_effect_via_talent() {
    ++rank_talent;
    // TODO: Assert max rank?
    proc_range = talent_ranks[rank_talent] * 100;
}

void UnbridledWrath::decrease_effect_via_talent() {
    --rank_talent;
    assert(rank_talent >= 0);
    proc_range = talent_ranks[rank_talent] * 100;
}
