#include "RelentlessStrikes.h"

#include "ClassStatistics.h"
#include "ProcInfo.h"
#include "Rogue.h"
#include "StatisticsResource.h"

RelentlessStrikes::RelentlessStrikes(Rogue* rogue) :
    Proc("Relentless Strikes",
         "Assets/ability/Ability_warrior_decisivestrike.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         rogue),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Relentless Strikes", 1, DisabledAtZero::Yes)}),
    statistics_resource(nullptr),
    rogue(rogue),
    talent_ranks({0, 2000}) {
    this->enabled = false;

    proc_range = talent_ranks[0];
}

void RelentlessStrikes::proc_effect() {
    unsigned before_gain = rogue->get_resource_level(ResourceType::Energy);

    rogue->gain_energy(25);

    unsigned delta = rogue->get_resource_level(ResourceType::Energy) - before_gain;
    statistics_resource->add_resource_gain(ResourceType::Energy, delta);
}

void RelentlessStrikes::set_current_combo_points(const unsigned combo_points) {
    proc_range = combo_proc_percent * combo_points;
}

void RelentlessStrikes::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
    combo_proc_percent = talent_ranks[curr];
}

void RelentlessStrikes::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
    combo_proc_percent = talent_ranks[curr];
}

void RelentlessStrikes::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
