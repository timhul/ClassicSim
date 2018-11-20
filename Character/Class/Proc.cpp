
#include "Proc.h"

#include <utility>
#include "EnabledProcs.h"
#include "Random.h"
#include "ClassStatistics.h"
#include "StatisticsSpell.h"
#include "StatisticsProc.h"
#include "StatisticsResource.h"
#include "Character.h"

Proc::Proc(const QString& name,
           const QString &icon,
           const double proc_rate,
           const double inner_cooldown,
           const QVector<Proc *>& linked_procs,
           QVector<ProcInfo::Source>  proc_sources,
           Character* pchar) :
    Spell(name, icon, pchar, RestrictedByGcd::No, inner_cooldown, ResourceType::Rage, 0),
    procs(pchar->get_enabled_procs()),
    random(new Random(0, 9999)),
    proc_sources(std::move(proc_sources)),
    statistics_proc(nullptr),
    statistics_resource(nullptr)
{
    this->proc_range = static_cast<unsigned>(round(proc_rate * 10000));
    this->linked_procs = linked_procs;
}

Proc::~Proc() {
    delete random;
}

void Proc::spell_effect() {
    statistics_proc->increment_attempt();

    if (random->get_roll() < get_proc_range() && proc_specific_conditions_fulfilled()) {
        proc_effect();
        statistics_proc->increment_proc();

        for (auto & linked_proc : linked_procs) {
            linked_proc->spell_effect();
        }
    }
}

unsigned Proc::get_proc_range() const {
    return proc_range;
}

void Proc::enable_proc() {
    procs->add_proc_effect(this);
}

void Proc::disable_proc() {
    procs->remove_proc_effect(this->instance_id);
}

void Proc::set_current_proc_source(const ProcInfo::Source source) {
    this->curr_proc_source = source;
}

bool Proc::procs_from_source(ProcInfo::Source source) const {
    return proc_sources.contains(source);
}

void Proc::prepare_set_of_combat_iterations() {
    this->statistics_proc = pchar->get_statistics()->get_proc_statistics(name, icon);
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}

bool Proc::proc_specific_conditions_fulfilled() const {
    return true;
}
