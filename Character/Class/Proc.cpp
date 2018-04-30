
#include "Proc.h"
#include "Random.h"

Proc::Proc(const QString& name, const float proc_rate, const float inner_cooldown,
           const bool recursive, const QVector<Proc *> linked_procs,
           Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell(name, engine, pchar, roll, inner_cooldown, 0),
    random(new Random(0, 99))
{
    this->proc_range = round(proc_rate * 100);
    this->recursive = recursive;
    this->linked_procs = linked_procs;
}

Proc::~Proc() {
    delete random;
}

int Proc::spell_effect(const int) {
    if (random->get_roll() < proc_range) {
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
