#include "DeepWounds.h"

#include <cmath>

#include "CooldownControl.h"
#include "DotTick.h"
#include "Engine.h"
#include "NoEffectUniqueDebuff.h"
#include "Utils/Check.h"
#include "Warrior.h"

DeepWounds::DeepWounds(Character* pchar) :
    SpellPeriodic("Deep Wounds", "Assets/ability/Ability_backstab.png", pchar,
                  new NoEffectUniqueDebuff(pchar, Priority::Trash, 12, "Deep Wounds", "Assets/ability/Ability_backstab.png", Hidden::No),
                  RestrictedByGcd::No, ResourceType::Rage, 2.0, 0, 1),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Deep Wounds", 3, DisabledAtZero::Yes)}),
    warr(dynamic_cast<Warrior*>(pchar)),
    talent_ranks({0.0, 0.2, 0.4, 0.6})
{
    this->enabled = false;
}

DeepWounds::~DeepWounds() {
    delete marker_buff;
}

bool DeepWounds::check_application_success() {
    return true;
}

void DeepWounds::new_application_effect() {
    stacks.append(6);
}

void DeepWounds::refresh_effect() {
    new_application_effect();
}

void DeepWounds::tick_effect() {
    double damage_dealt = (warr->get_avg_mh_damage() * wpn_percent) / 6;

    damage_dealt += previous_tick_rest;
    previous_tick_rest = damage_dealt - round(damage_dealt);

    for (int & stack : stacks) {
        check((stack > 0), "Deep wounds encountered empty stack");
        --stack;
    }

    stacks.removeAll(0);

    if (!stacks.empty())
        add_next_tick();
    else
        previous_tick_rest = 0;

    add_hit_dmg(static_cast<int>(round(damage_dealt)), 0, 0);
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
