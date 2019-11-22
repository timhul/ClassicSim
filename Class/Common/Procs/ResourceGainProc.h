#pragma once

#include "Proc.h"

class Random;
class StatisticsResource;

class ResourceGainProc: public Proc {
public:
    ResourceGainProc(Character* pchar,
                     const QString& proc_name,
                     const QString& icon,
                     const QVector<ProcInfo::Source>& proc_sources,
                     const double proc_rate,
                     const ResourceType gain_resource_type,
                     const unsigned min_gain,
                     const unsigned max_gain);
    ~ResourceGainProc() override;

private:
    Random* gain_roll;
    StatisticsResource* statistics_resource;

    const ResourceType gain_resource_type;

    void proc_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};
