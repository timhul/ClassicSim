#ifndef ACTIVEPROCS_H
#define ACTIVEPROCS_H

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

class EnabledProcs {
public:
    EnabledProcs(Character* pchar, Faction* faction);
    ~EnabledProcs();

    void run_proc_effects(ProcInfo::Source);
    void add_proc_effect(Proc* proc);
    void remove_proc_effect(const int instance_id);

    void clear_all();
    void reset();

    void switch_faction();

    void prepare_set_of_combat_iterations();

private:
    Character* pchar;
    Faction* faction;
    GeneralProcs* general_procs;

    int next_instance_id;

    QVector<Proc*> enabled_procs;
};

#endif // ACTIVEPROCS_H
