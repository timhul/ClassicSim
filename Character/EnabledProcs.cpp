#include "Character.h"
#include "EnabledProcs.h"
#include "Faction.h"
#include "GeneralProcs.h"
#include "Proc.h"

EnabledProcs::EnabledProcs(Character* pchar, Faction* faction) :
    pchar(pchar),
    faction(faction),
    general_procs(new GeneralProcs(pchar, faction)),
    next_instance_id(ProcStatus::INITIAL_ID)
{}

EnabledProcs::~EnabledProcs()
{
    delete general_procs;
}

void EnabledProcs::run_proc_effects(ProcInfo::Source source) {
    assert(source != ProcInfo::Source::Manual);

    for (auto & proc : enabled_procs) {
        if (proc->procs_from_source(source)) {
            proc->set_current_proc_source(source);
            proc->perform();
        }
    }
}

void EnabledProcs::add_proc_effect(Proc* proc) {
    enabled_procs.append(proc);

    if (proc->get_instance_id() == ProcStatus::INACTIVE) {
        proc->set_instance_id(next_instance_id);
        ++next_instance_id;
    }
}

void EnabledProcs::remove_proc_effect(const int instance_id) {
    if (instance_id == ProcStatus::INACTIVE)
        return;

    for (int i = 0; i < enabled_procs.size(); ++i) {
        if (enabled_procs.at(i)->get_instance_id() == instance_id)
            return enabled_procs.removeAt(i);
    }
}

void EnabledProcs::clear_all() {
    for (auto & proc : enabled_procs)
        proc->disable_proc();
}

void EnabledProcs::reset() {
    for (auto & proc : enabled_procs)
        proc->reset();
}

void EnabledProcs::switch_faction() {
    general_procs->switch_faction();
}

void EnabledProcs::prepare_set_of_combat_iterations() {
    for (auto & proc : enabled_procs)
        proc->prepare_set_of_combat_iterations();
}
