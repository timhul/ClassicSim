#include "ResourceGainProc.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "ClassStatistics.h"
#include "ProcInfo.h"
#include "Random.h"
#include "StatisticsResource.h"

ResourceGainProc::ResourceGainProc(Character* pchar_,
                                   const QString& proc_name,
                                   const QString& icon_,
                                   const QVector<ProcInfo::Source>& proc_sources_,
                                   const double proc_rate,
                                   const ResourceType gain_resource_type,
                                   const unsigned min_gain,
                                   const unsigned max_gain) :
    Proc(proc_name, icon_, proc_rate, 0, QVector<Proc*>(), proc_sources_, pchar_),
    gain_roll(new Random(min_gain, max_gain)),
    statistics_resource(nullptr),
    gain_resource_type(gain_resource_type)
{}

ResourceGainProc::~ResourceGainProc() {
    delete gain_roll;
}

void ResourceGainProc::proc_effect() {
    const unsigned resource_gain = gain_roll->get_roll();

    const unsigned resource_before = pchar->get_resource_level(gain_resource_type);
    pchar->gain_resource(gain_resource_type, resource_gain);

    const unsigned delta = pchar->get_resource_level(gain_resource_type) - resource_before;

    if (delta > 0)
        statistics_resource->add_resource_gain(gain_resource_type, delta);
}

void ResourceGainProc::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
