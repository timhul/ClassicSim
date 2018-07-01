
#include "ActiveProcs.h"
#include "Proc.h"
#include "GeneralProcs.h"
#include "Character.h"
#include "Faction.h"

ActiveProcs::ActiveProcs(Character* pchar, Faction* faction, QObject* parent) :
    QObject(parent),
    pchar(pchar),
    faction(faction),
    general_procs(new GeneralProcs(pchar, faction)),
    next_instance_id(ProcStatus::INITIAL_ID)
{}

ActiveProcs::~ActiveProcs()
{
    delete general_procs;
}

void ActiveProcs::run_proc_effects(ProcInfo::Source source) {
    for (int i = 0; i < active_procs.size(); ++i) {
        if (active_procs[i]->procs_from_source(source))
            active_procs[i]->perform();
    }
}

void ActiveProcs::add_proc_effect(Proc* proc) {
    active_procs.append(proc);

    if (proc->get_instance_id() == ProcStatus::INACTIVE) {
        proc->set_instance_id(next_instance_id);
        ++next_instance_id;
    }
}

void ActiveProcs::remove_proc_effect(const int instance_id) {
    if (instance_id == ProcStatus::INACTIVE)
        return;

    for (int i = 0; i < active_procs.size(); ++i) {
        if (active_procs.at(i)->get_instance_id() == instance_id)
            return active_procs.removeAt(i);
    }
}

void ActiveProcs::reset() {
    for (int i = 0; i < active_procs.size(); ++i) {
        active_procs[i]->reset();
    }
}

void ActiveProcs::switch_faction() {
    general_procs->switch_faction();
}
