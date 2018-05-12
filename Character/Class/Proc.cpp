
#include "Proc.h"
#include "Random.h"
#include "StatisticsBuff.h"
#include "StatisticsResource.h"

Proc::Proc(const QString& name, const float proc_rate, const float inner_cooldown,
           const bool recursive, const QVector<Proc *> linked_procs,
           Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell(name, engine, pchar, roll, inner_cooldown, 0),
    random(new Random(0, 9999)),
    statistics_buff(new StatisticsBuff(name)),
    statistics_resource(new StatisticsResource(name))
{
    this->proc_range = round(proc_rate * 10000);
    this->recursive = recursive;
    this->linked_procs = linked_procs;
}

Proc::~Proc() {
    delete random;
    delete statistics_buff;
    delete statistics_resource;
}

int Proc::spell_effect(const int) {
    if (random->get_roll() < get_proc_range()) {
        proc_effect();

        for (int i = 0; i < linked_procs.size(); ++i) {
            linked_procs[i]->spell_effect(0);
        }
    }

    return 0;
}

int Proc::get_proc_range() const {
    return proc_range;
}

StatisticsBuff* Proc::get_statistics_for_buff() const {
    return statistics_buff;
}

StatisticsResource* Proc::get_statistics_for_resource() const {
    return statistics_resource;
}
