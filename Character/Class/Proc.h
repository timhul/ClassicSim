#ifndef PROC_H
#define PROC_H

#include "Spell.h"
#include "ProcInfo.h"

class ActiveProcs;
class StatisticsProc;
class StatisticsBuff;
class StatisticsResource;

class Proc: public Spell {
public:
    Proc(const QString &name,
         const double proc_rate,
         const double inner_cooldown,
         const QVector<Proc *>& linked_procs,
         QVector<ProcInfo::Source>  proc_sources,
         Character* pchar);
    ~Proc() override;

    virtual unsigned get_proc_range() const;

    void enable_proc();
    void disable_proc();

    int get_instance_id() const;
    void set_instance_id(const int);
    void set_current_proc_source(const ProcInfo::Source);

    bool procs_from_source(ProcInfo::Source) const;

    void prepare_set_of_combat_iterations() override;

protected:
    ActiveProcs* procs;
    Random* random;
    QVector<unsigned> talent_ranks;
    QVector<Proc*> linked_procs;
    QVector<ProcInfo::Source> proc_sources;
    ProcInfo::Source curr_proc_source{};
    StatisticsProc* statistics_proc;
    StatisticsBuff* statistics_buff;
    StatisticsResource* statistics_resource;

    int instance_id;

    unsigned proc_range;

    void spell_effect() override;
    virtual void proc_effect() = 0;
    virtual bool proc_specific_conditions_fulfilled() const;
private:
};

#endif // PROC_H
