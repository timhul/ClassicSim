#ifndef PROC_H
#define PROC_H

#include "Spell.h"

class StatisticsProc;
class StatisticsBuff;
class StatisticsResource;

class Proc: public Spell {
public:
    Proc(const QString &name, const float proc_rate, const float inner_cooldown,
         const bool recursive, const QVector<Proc *> linked_procs,
         Engine* engine, Character* pchar, CombatRoll* roll);
    ~Proc();

    int spell_effect(const int) override;
    virtual void proc_effect() = 0;

    virtual int get_proc_range() const;

    StatisticsProc* get_statistics_for_proc() const;
    StatisticsBuff* get_statistics_for_buff() const;
    StatisticsResource* get_statistics_for_resource() const;

protected:
    Random* random;
    QVector<int> talent_ranks;
    QVector<Proc*> linked_procs;
    StatisticsProc* statistics_proc;
    StatisticsBuff* statistics_buff;
    StatisticsResource* statistics_resource;

    int proc_range;
    bool recursive;
private:
};

#endif // PROC_H
