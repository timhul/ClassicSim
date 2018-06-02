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
    Proc(const QString &name, const float proc_rate, const float inner_cooldown,
         const bool recursive, const QVector<Proc *> linked_procs,
         const QVector<ProcInfo::Source> proc_sources,
         Engine* engine, Character* pchar, CombatRoll* roll);
    ~Proc();

    int spell_effect(const int) override;
    virtual void proc_effect() = 0;
    virtual int get_proc_range() const;

    void enable_proc();
    void disable_proc();

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
    StatisticsProc* statistics_proc;
    StatisticsBuff* statistics_buff;
    StatisticsResource* statistics_resource;

    int proc_range;
    bool recursive;
private:
};

#endif // PROC_H
