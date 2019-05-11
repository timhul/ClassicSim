#include "Bloodrage.h"

#include "ClassStatistics.h"
#include "Engine.h"
#include "ResourceGain.h"
#include "StatisticsResource.h"
#include "Warrior.h"

Bloodrage::Bloodrage(Character* pchar) :
    Spell("Bloodrage", "Assets/ability/Ability_racial_bloodrage.png", pchar, RestrictedByGcd::No, 60, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Bloodrage", 2, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar))
{}

SpellStatus Bloodrage::is_ready_spell_specific() const {
    return warr->in_defensive_stance() ? SpellStatus::InDefensiveStance : SpellStatus::Available;
}

void Bloodrage::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}

void Bloodrage::increase_talent_rank_effect(const QString&, const int curr) {
    this->immediate_rage_gain = talent_ranks[curr];
}

void Bloodrage::decrease_talent_rank_effect(const QString&, const int curr) {
    this->immediate_rage_gain = talent_ranks[curr];
}

void Bloodrage::gain_rage(const unsigned rage_gain) {
    const unsigned before = warr->get_resource_level(ResourceType::Rage);

    warr->gain_rage(rage_gain);

    const unsigned gain_after_cap = warr->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}

void Bloodrage::spell_effect() {
    add_spell_cd_event();

    auto new_event = new ResourceGain(pchar, this, engine->get_current_priority() + 1.0);
    this->engine->add_event(new_event);
    periodic_rage_current = periodic_rage_base;

    gain_rage(immediate_rage_gain);
}

void Bloodrage::perform_periodic() {
    gain_rage(1);
    --periodic_rage_current;

    if (periodic_rage_current == 0)
        return;

    auto new_event = new ResourceGain(pchar, this, engine->get_current_priority() + 1.0);
    this->engine->add_event(new_event);
}
