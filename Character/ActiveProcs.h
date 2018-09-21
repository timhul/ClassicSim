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

namespace ProcStatus {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

class ActiveProcs: public QObject {
    Q_OBJECT

public:
    ActiveProcs(Character* pchar, Faction* faction, QObject* parent = nullptr);
    ~ActiveProcs();

    void run_proc_effects(ProcInfo::Source);
    void add_proc_effect(Proc* proc);
    void remove_proc_effect(const int instance_id);

    void reset();

    void switch_faction();

private:
    Character* pchar;
    Faction* faction;
    GeneralProcs* general_procs;

    int next_instance_id;

    QVector<Proc*> active_procs;
};

#endif // ACTIVEPROCS_H
