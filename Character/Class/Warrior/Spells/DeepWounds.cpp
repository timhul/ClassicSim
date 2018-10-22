
#include "DeepWounds.h"
#include "Warrior.h"
#include "DotTick.h"

DeepWounds::DeepWounds(Character* pchar) :
    Spell("Deep Wounds", "Assets/warrior/arms/tier3/Ability_backstab.png", pchar, false, 3, 0),
    TalentRequirer(3, DisabledAtZero::Yes),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;

    this->previous_tick_rest = 0;
    this->talent_ranks = {0.0, 0.2, 0.4, 0.6};
    wpn_percent = talent_ranks[curr_talent_rank];
}

void DeepWounds::spell_effect() {
    assert(!stacks.empty());

    double damage_dealt = stacks.size() * ((warr->get_avg_mh_damage() * wpn_percent) / 6);

    // TODO: previous_tick_rest not correctly increased/decreased by dmg increasing effects
    // occuring since the previous tick was calculated. This effect is VERY minor.
    damage_dealt += previous_tick_rest;
    previous_tick_rest = damage_dealt - round(damage_dealt);

    for (int & stack : stacks) {
        assert(stack > 0);
        --stack;
    }

    stacks.removeAll(0);

    if (!stacks.empty()) {
        auto* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }
    else
        previous_tick_rest = 0;

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost);
}

void DeepWounds::apply_debuff() {
    if (!is_enabled())
        return;

    // TODO: Assumption is that each stack ticks 6 times (i.e. every 2 seconds).
    // After the first critical strike (T=0), the first tick comes at T=2, next at T=4, and so on.
    if (stacks.empty()) {
        auto* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }

    stacks.append(6);
}

void DeepWounds::reset_effect() {
    stacks.clear();
    previous_tick_rest = 0;
}

void DeepWounds::increase_talent_rank_effect(const QString&) {
    wpn_percent = talent_ranks[curr_talent_rank];
}

void DeepWounds::decrease_talent_rank_effect(const QString&) {
    wpn_percent = talent_ranks[curr_talent_rank];
}
