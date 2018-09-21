
#include "Proc.h"
#include "ActiveProcs.h"
#include "Random.h"
#include "ClassStatistics.h"
#include "StatisticsSpell.h"
#include "StatisticsProc.h"
#include "StatisticsBuff.h"
#include "StatisticsResource.h"
#include "Character.h"

Proc::Proc(const QString& name, const double proc_rate, const double inner_cooldown,
           const bool recursive, const QVector<Proc *> linked_procs,
           const QVector<ProcInfo::Source> proc_sources,
           Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell(name, engine, pchar, roll, false, inner_cooldown, 0),
    procs(pchar->get_active_procs()),
    random(new Random(0, 9999)),
    proc_sources(proc_sources),
    statistics_proc(new StatisticsProc(name)),
    statistics_buff(new StatisticsBuff(name)),
    statistics_resource(new StatisticsResource(name)),
    instance_id(ProcStatus::INACTIVE)
{
    this->proc_range = static_cast<int>(round(proc_rate * 10000));
    this->recursive = recursive;
    this->linked_procs = linked_procs;
}

Proc::~Proc() {
    delete random;
    delete statistics_proc;
    delete statistics_buff;
    delete statistics_resource;
}

void Proc::spell_effect() {
    statistics_proc->increment_attempt();

    if (random->get_roll() < get_proc_range()) {
        proc_effect();
        statistics_proc->increment_proc();

        for (int i = 0; i < linked_procs.size(); ++i) {
            linked_procs[i]->spell_effect();
        }
    }
}

int Proc::get_proc_range() const {
    return proc_range;
}

void Proc::enable_proc() {
    this->add_proc_statistic();
    procs->add_proc_effect(this);
}

void Proc::disable_proc() {
    this->remove_proc_statistic();
    procs->remove_proc_effect(this->instance_id);
}

int Proc::get_instance_id() const {
    return this->instance_id;
}

void Proc::set_instance_id(const int instance_id) {
    this->instance_id = instance_id;
}

void Proc::set_current_proc_source(const ProcInfo::Source source) {
    this->curr_proc_source = source;
}

bool Proc::procs_from_source(ProcInfo::Source source) const {
    return proc_sources.contains(source);
}

void Proc::add_proc_statistic() {
    pchar->get_statistics()->add_proc_statistics(this->statistics_proc);
    pchar->get_statistics()->add_buff_statistics(this->statistics_buff);
    pchar->get_statistics()->add_resource_statistics(this->statistics_resource);
    pchar->get_statistics()->add_spell_statistics(get_statistics_for_spell());
}

void Proc::remove_proc_statistic() {
    pchar->get_statistics()->remove_proc_statistics(this->statistics_proc->get_name());
    pchar->get_statistics()->remove_buff_statistics(this->statistics_buff->get_name());
    pchar->get_statistics()->remove_resource_statistics(this->statistics_resource->get_name());
    pchar->get_statistics()->remove_spell_statistics(get_statistics_for_spell()->get_name());
}

StatisticsProc* Proc::get_statistics_for_proc() const {
    return statistics_proc;
}

StatisticsBuff* Proc::get_statistics_for_buff() const {
    return statistics_buff;
}

StatisticsResource* Proc::get_statistics_for_resource() const {
    return statistics_resource;
}
