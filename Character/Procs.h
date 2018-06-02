#ifndef PROCS_H
#define PROCS_H

#include <QObject>
#include <QVector>

#include "ProcInfo.h"

class Character;
class GeneralProcs;
class Proc;
class Engine;
class CombatRoll;
class Faction;

class Procs: public QObject {
    Q_OBJECT

public:
    Procs(Character* pchar, Faction* faction, QObject* parent = 0);
    ~Procs();

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

#endif // PROCS_H
