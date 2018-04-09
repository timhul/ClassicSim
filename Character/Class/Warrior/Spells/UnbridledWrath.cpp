
#include "UnbridledWrath.h"
#include "Random.h"
#include "Warrior.h"

UnbridledWrath::UnbridledWrath(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Unbridled Wrath", engine, pchar, roll, 0, 0),
    random(new Random(0, 99))
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    talent_ranks = {0, 8, 16, 24, 32, 40};

    proc_range = talent_ranks[rank_talent];
}

UnbridledWrath::~UnbridledWrath() {
    delete random;
}

int UnbridledWrath::spell_effect(const int) {
    int rage = 0;
    if (random->get_roll() < proc_range) {
        add_proc_stats(1, "Rage gain");
        rage = 1;
    }

    return rage;
}

void UnbridledWrath::increase_effect_via_talent() {
    ++rank_talent;
    // TODO: Assert max rank?
    proc_range = talent_ranks[rank_talent];
}

void UnbridledWrath::decrease_effect_via_talent() {
    --rank_talent;
    assert(rank_talent >= 0);
    proc_range = talent_ranks[rank_talent];
}
