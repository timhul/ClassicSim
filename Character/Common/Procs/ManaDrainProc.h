#ifndef MANADRAINPROC_H
#define MANADRAINPROC_H

#include "Proc.h"

class Random;
class StatisticsResource;

class ManaDrainProc: public Proc {
public:
    ManaDrainProc(Character* pchar,
                     const QString& proc_name,
                     const QString &icon,
                     const QVector<ProcInfo::Source>& proc_sources,
                     const double proc_rate,
                     const unsigned min_drain,
                     const unsigned max_drain);
    ~ManaDrainProc() override;

private:
    Random* drain_roll;
    StatisticsResource* statistics_resource;

    void proc_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // MANADRAINPROC_H
