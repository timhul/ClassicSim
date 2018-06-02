#ifndef ACTIVEPROCS_H
#define ACTIVEPROCS_H

#include <QObject>
#include <QVector>

#include "ProcInfo.h"

class Character;
class GeneralProcs;
class Proc;
class Engine;
class CombatRoll;
class Faction;

class ActiveProcs: public QObject {
    Q_OBJECT

public:
    ActiveProcs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~ActiveProcs();

    void run_proc_effects(ProcInfo::Source);
    void add_proc_effect(Proc* proc);
    void remove_proc_effect(const Proc* proc);

    void reset();

    void switch_faction();

private:
    Character* pchar;
    Faction* faction;
    GeneralProcs* general_procs;

    QVector<Proc*> active_procs;
};

#endif // ACTIVEPROCS_H
