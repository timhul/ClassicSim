#include "DeepWounds.h"

#include "DotTick.h"
#include "Engine.h"
#include "NoEffectBuff.h"
#include "Utils/Check.h"
#include "Warrior.h"

DeepWounds::DeepWounds(Character* pchar) :
    Spell("Deep Wounds", "Assets/ability/Ability_backstab.png", pchar, RestrictedByGcd::No, 0, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Deep Wounds", 3, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    buff(new NoEffectBuff(pchar,
                          12,
                          "Deep Wounds",
                          "Assets/ability/Ability_backstab.png",
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
    check(!stacks.empty(), "No deep wounds stacks to consume");

    double damage_dealt = stacks.size() * ((warr->get_avg_mh_damage() * wpn_percent) / 6);

    damage_dealt += previous_tick_rest;
    previous_tick_rest = damage_dealt - round(damage_dealt);

    for (int & stack : stacks) {
        check((stack > 0), "Deep wounds encountered empty stack");
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

void DeepWounds::increase_talent_rank_effect(const QString&, const int curr) {
    wpn_percent = talent_ranks[curr];
}

void DeepWounds::decrease_talent_rank_effect(const QString&, const int curr) {
    wpn_percent = talent_ranks[curr];
}

void DeepWounds::enable_spell_effect() {
    buff->enable_buff();
}

void DeepWounds::disable_spell_effect() {
    buff->disable_buff();
}
