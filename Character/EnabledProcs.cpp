#include "EnabledProcs.h"

#include "Character.h"
#include "Faction.h"
#include "GeneralProcs.h"
#include "Proc.h"
#include "Utils/Check.h"

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

void EnabledProcs::ignore_proc_in_next_proc_check(const int instance_id) {
    procced_instance_ids.insert(instance_id);
}

void EnabledProcs::run_proc_effects(ProcInfo::Source source) {
    check((source != ProcInfo::Source::Manual), "Cannot run proc effects on manually triggered proc");

    for (const auto & proc : enabled_procs) {
        if (!proc->procs_from_source(source))
            continue;
        if (procced_instance_ids.contains(proc->get_instance_id()))
            continue;

        proc->set_current_proc_source(source);

        if (!proc->check_proc_success())
            continue;

        procced_instance_ids.insert(proc->get_instance_id());
        proc->perform();
    }

    procced_instance_ids.clear();
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
    for (const auto & proc : enabled_procs)
        proc->disable_proc();
}

void EnabledProcs::reset() {
    for (const auto & proc : enabled_procs)
        proc->reset();

    procced_instance_ids.clear();
}

void EnabledProcs::switch_faction() {
    general_procs->switch_faction();
}

void EnabledProcs::prepare_set_of_combat_iterations() {
    for (const auto & proc : enabled_procs)
        proc->prepare_set_of_combat_iterations();
}
