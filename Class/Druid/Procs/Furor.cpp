#include "Furor.h"

#include "ClassStatistics.h"
#include "Druid.h"
#include "ProcInfo.h"
#include "StatisticsResource.h"

Furor::Furor(Druid* druid) :
    Proc("Furor", "Assets/spell/Spell_holy_blessingofstamina.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         druid),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Furor", 5, DisabledAtZero::Yes)}),
    statistics_resource(nullptr),
    druid(druid)
{
    this->enabled = false;

    proc_range = talent_ranks[0];
}

void Furor::proc_effect() {
    const unsigned before_gain = druid->get_resource_level(ResourceType::Energy);

    druid->gain_energy(40);

    const unsigned delta = druid->get_resource_level(ResourceType::Energy) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Energy, delta);
}

void Furor::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void Furor::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void Furor::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
