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
                     const unsigned min_drain,
                     const unsigned max_drain);
    ~ResourceGainProc() override;

private:
    Random* drain_roll;
    StatisticsResource* statistics_resource;

    void proc_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};
