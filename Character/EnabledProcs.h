#pragma once

#include <QSet>
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
} // namespace ProcStatus

class EnabledProcs {
public:
    EnabledProcs(Character* pchar, Faction* faction);
    ~EnabledProcs();

    void ignore_proc_in_next_proc_check(const int instance_id);
    void run_proc_check(ProcInfo::Source);
    void add_proc(Proc* proc);
    void remove_proc_effect(const int instance_id);

    void clear_all();
    void reset();

    void switch_faction();

    void prepare_set_of_combat_iterations();

    bool proc_enabled(Proc* proc) const;

private:
    Character* pchar;
    Faction* faction;
    GeneralProcs* general_procs;

    int next_instance_id;
    int procs_in_progress {0};

    QVector<Proc*> enabled_procs;
    QSet<int> procced_instance_ids;
};
