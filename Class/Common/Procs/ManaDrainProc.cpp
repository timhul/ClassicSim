#include "ManaDrainProc.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "ClassStatistics.h"
#include "ProcInfo.h"
#include "Random.h"
#include "StatisticsResource.h"

ManaDrainProc::ManaDrainProc(Character* pchar,
                             const QString& proc_name,
                             const QString& icon,
                             const QVector<ProcInfo::Source>& proc_sources,
                             const double proc_rate,
                             const unsigned min_drain,
                             const unsigned max_drain) :
    Proc(proc_name, icon, proc_rate, 0, QVector<Proc*>(), proc_sources, pchar),
    drain_roll(new Random(min_drain, max_drain)),
    statistics_resource(nullptr)
{}

ManaDrainProc::~ManaDrainProc() {
    delete drain_roll;
}

void ManaDrainProc::proc_effect() {
    unsigned mana_gain = drain_roll->get_roll();

    unsigned mana_before = pchar->get_resource_level(ResourceType::Mana);
    pchar->gain_mana(mana_gain);

    unsigned delta = pchar->get_resource_level(ResourceType::Mana) - mana_before;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

void ManaDrainProc::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
