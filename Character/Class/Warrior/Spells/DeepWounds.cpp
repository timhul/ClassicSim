
#include "DeepWounds.h"
#include "Warrior.h"
#include "DotTick.h"

DeepWounds::DeepWounds(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Deep Wounds", engine, pchar, roll, false, 3, 0),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->previous_tick_rest = 0;
    this->ranks = {0.0, 0.2, 0.4, 0.6};
    this->rank_talent = 0;
}

void DeepWounds::spell_effect() {
    assert(!stacks.empty());

    double damage_dealt = stacks.size() * ((warr->get_avg_mh_damage() * ranks[rank_talent]) / 6);

    // TODO: previous_tick_rest not correctly increased/decreased by dmg increasing effects
    // occuring since the previous tick was calculated. This effect is VERY minor.
    damage_dealt += previous_tick_rest;
    previous_tick_rest = damage_dealt - round(damage_dealt);

    for (int i = 0; i < stacks.size(); ++i) {
        assert(stacks[i] > 0);
        --stacks[i];
    }

    stacks.removeAll(0);

    if (!stacks.empty()) {
        DotTick* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }
    else
        previous_tick_rest = 0;

    add_hit_dmg(static_cast<int>(round(damage_dealt)));
}

void DeepWounds::apply_debuff() {
    if (!is_enabled())
        return;

    // TODO: Assumption is that each stack ticks 6 times (i.e. every 2 seconds).
    // After the first critical strike (T=0), the first tick comes at T=2, next at T=4, and so on.
    if (stacks.empty()) {
        DotTick* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }

    stacks.append(6);
}

void DeepWounds::reset_effect() {
    stacks.clear();
    previous_tick_rest = 0;
}
