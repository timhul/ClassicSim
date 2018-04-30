#ifndef PROC_H
#define PROC_H

#include "Spell.h"

class Proc: public Spell {
public:
    Proc(const QString &name, const float proc_rate, const float inner_cooldown,
         const bool recursive, const QVector<Proc *> linked_procs,
         Engine* engine, Character* pchar, CombatRoll* roll);
    ~Proc();

    int spell_effect(const int) override;
    virtual void proc_effect() = 0;

    virtual int get_proc_range() const;

protected:
    Random* random;
    QVector<int> talent_ranks;
    QVector<Proc*> linked_procs;
    int proc_range;
    bool recursive;
private:
};

#endif // PROC_H
