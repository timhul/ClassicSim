
#include "DeepWounds.h"
#include "Warrior.h"
#include "DotTick.h"

DeepWounds::DeepWounds(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Deep Wounds", engine, pchar, roll, 3, 0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int DeepWounds::spell_effect(const int) {
    assert(!stacks.empty());

    // TODO: Remove hardcoded assumption of 3/3 Deep Wounds.
    int damage_dealt = stacks.size() * ((pchar->get_avg_mh_damage() * 0.6) / 6);
    for (int i = 0; i < stacks.size(); ++i) {
        assert(stacks[i] > 0);
        --stacks[i];
    }

    stacks.removeAll(0);

    if (!stacks.empty()) {
        DotTick* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }

    add_success_stats("Hit", damage_dealt);

    return 0;
}

void DeepWounds::apply_debuff() {
    // TODO: Assumption is that each stack ticks 6 times (i.e. every 2 seconds).
    // After the first critical strike (T=0), the first tick comes at T=2, next at T=4, and so on.
    if (stacks.empty()) {
        DotTick* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }

    stacks.append(6);
}
