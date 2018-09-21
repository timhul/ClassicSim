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
    Proc(const QString &name, const double proc_rate, const double inner_cooldown,
         const bool recursive, const QVector<Proc *> linked_procs,
         const QVector<ProcInfo::Source> proc_sources,
         Engine* engine, Character* pchar, CombatRoll* roll);
    ~Proc() override;

    void spell_effect() override;
    virtual void proc_effect() = 0;
    virtual int get_proc_range() const;

    void enable_proc();
    void disable_proc();

    int get_instance_id() const;
    void set_instance_id(const int);
    void set_current_proc_source(const ProcInfo::Source);

    bool procs_from_source(ProcInfo::Source) const;

    StatisticsProc* get_statistics_for_proc() const;
    StatisticsBuff* get_statistics_for_buff() const;
    StatisticsResource* get_statistics_for_resource() const;

    void add_proc_statistic();
    void remove_proc_statistic();

protected:
    ActiveProcs* procs;
    Random* random;
    QVector<int> talent_ranks;
    QVector<Proc*> linked_procs;
    QVector<ProcInfo::Source> proc_sources;
    ProcInfo::Source curr_proc_source;
    StatisticsProc* statistics_proc;
    StatisticsBuff* statistics_buff;
    StatisticsResource* statistics_resource;

    int instance_id;

    int proc_range;
    bool recursive;
private:
};

#endif // PROC_H
