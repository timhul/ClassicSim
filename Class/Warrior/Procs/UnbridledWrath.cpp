#include "UnbridledWrath.h"

#include "ClassStatistics.h"
#include "ProcInfo.h"
#include "StatisticsResource.h"
#include "Warrior.h"

UnbridledWrath::UnbridledWrath(Character* pchar) :
    Proc("Unbridled Wrath", "Assets/spell/Spell_nature_stoneclawtotem.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell,
                                    ProcInfo::Source::MainhandSwing,
                                    ProcInfo::Source::OffhandSwing}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Unbridled Wrath", 5, DisabledAtZero::Yes)}),
    statistics_resource(nullptr),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
    this->talent_ranks = {0, 800, 1600, 2400, 3200, 4000};
    proc_range = talent_ranks[0];
}

UnbridledWrath::~UnbridledWrath() = default;

void UnbridledWrath::proc_effect() {
    unsigned rage = warr->get_resource_level(resource_type);
    warr->gain_rage(1);

    if (warr->get_resource_level(resource_type) != rage)
        statistics_resource->add_resource_gain(ResourceType::Rage, 1);
}

void UnbridledWrath::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void UnbridledWrath::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void UnbridledWrath::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
