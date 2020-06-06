#include "Furor.h"

#include "ClassStatistics.h"
#include "Druid.h"
#include "ProcInfo.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

Furor::Furor(Druid* druid) :
    Proc("Furor",
         "Assets/spell/Spell_holy_blessingofstamina.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         druid),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Furor", 5, DisabledAtZero::Yes)}),
    statistics_resource(nullptr),
    druid(druid) {
    this->enabled = false;

    proc_range = talent_ranks[0];
}

void Furor::proc_effect() {
    if (druid->get_current_form() == DruidForm::Cat) {
        const unsigned before_gain = druid->get_resource_level(ResourceType::Energy);

        druid->gain_energy(40);

        const unsigned delta = druid->get_resource_level(ResourceType::Energy) - before_gain;
        statistics_resource->add_resource_gain(ResourceType::Energy, delta);
    } else if (druid->get_current_form() == DruidForm::Bear) {
        const unsigned before_gain = druid->get_resource_level(ResourceType::Rage);

        druid->gain_rage(10);

        const unsigned delta = druid->get_resource_level(ResourceType::Rage) - before_gain;
        statistics_resource->add_resource_gain(ResourceType::Rage, delta);
    } else {
        check(false, std::string("Furor::proc_effect called in invalid form "));
    }
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
