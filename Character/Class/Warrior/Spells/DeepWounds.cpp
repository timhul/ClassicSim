#include "DeepWounds.h"
#include "DotTick.h"
#include "NoEffectBuff.h"
#include "Warrior.h"

DeepWounds::DeepWounds(Character* pchar) :
    Spell("Deep Wounds", "Assets/warrior/arms/tier3/Ability_backstab.png", pchar, RestrictedByGcd::No, 0, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Deep Wounds", 3, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    buff(new NoEffectBuff(pchar,
                          12.0,
                          "Deep Wounds",
                          "Assets/warrior/arms/tier3/Ability_backstab.png",
                          Hidden::No,
                          Debuff::Yes))
{
    this->enabled = false;

    this->previous_tick_rest = 0;
    this->talent_ranks = {0.0, 0.2, 0.4, 0.6};
    wpn_percent = talent_ranks[0];
}

DeepWounds::~DeepWounds() {
    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
}

void DeepWounds::perform_periodic() {
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

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
}

void DeepWounds::spell_effect() {
    if (!is_enabled())
        return;

    buff->apply_buff();

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

void DeepWounds::increase_talent_rank_effect(const int curr, const QString&) {
    wpn_percent = talent_ranks[curr];
}

void DeepWounds::decrease_talent_rank_effect(const int curr, const QString&) {
    wpn_percent = talent_ranks[curr];
}

void DeepWounds::enable_spell_effect() {
    buff->enable_buff();
}

void DeepWounds::disable_spell_effect() {
    buff->disable_buff();
}
