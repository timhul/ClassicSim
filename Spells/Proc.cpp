#include "Proc.h"

#include <utility>

#include "Character.h"
#include "ClassStatistics.h"
#include "EnabledProcs.h"
#include "Random.h"
#include "StatisticsProc.h"
#include "StatisticsResource.h"
#include "StatisticsSpell.h"

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
    statistics_proc(nullptr)
{
    this->proc_range = static_cast<unsigned>(round(proc_rate * 10000));
    this->linked_procs = linked_procs;
}

Proc::~Proc() {
    delete random;
}

void Proc::spell_effect() {
    statistics_proc->increment_proc();

    proc_effect();

    for (const auto & linked_proc : linked_procs)
        linked_proc->spell_effect();
}

unsigned Proc::get_proc_range() const {
    return proc_range;
}

void Proc::enable_proc() {
    procs->add_proc(this);
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

bool Proc::check_proc_success() const {
    statistics_proc->increment_attempt();

    return random->get_roll() < get_proc_range() && proc_specific_conditions_fulfilled();
}

void Proc::prepare_set_of_combat_iterations() {
    this->statistics_proc = pchar->get_statistics()->get_proc_statistics(name, icon);
    prepare_set_of_combat_iterations_spell_specific();
}

bool Proc::proc_specific_conditions_fulfilled() const {
    return true;
}
