
#include "Bloodrage.h"
#include "Warrior.h"
#include "ResourceGain.h"

Bloodrage::Bloodrage(Character* pchar) :
    Spell("Bloodrage", "Assets/warrior/protection/tier2/Ability_racial_bloodrage.png", pchar, RestrictedByGcd::No, 60, ResourceType::Rage, 0),
    TalentRequirer(2, DisabledAtZero::No),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->talent_ranks = {10, 12, 15};
    this->immediate_rage_gain = talent_ranks[curr_talent_rank];
    this->periodic_rage_base = 10;
    this->periodic_rage_current = periodic_rage_base;
}

bool Bloodrage::is_ready_spell_specific() const {
    return !warr->in_defensive_stance();
}

void Bloodrage::increase_talent_rank_effect(const QString&) {
    this->immediate_rage_gain = talent_ranks[curr_talent_rank];
}

void Bloodrage::decrease_talent_rank_effect(const QString&) {
    this->immediate_rage_gain = talent_ranks[curr_talent_rank];
}

void Bloodrage::spell_effect() {
    add_spell_cd_event();

    auto* new_event = new ResourceGain(pchar, this, engine->get_current_priority() + 1.0);
    this->engine->add_event(new_event);
    periodic_rage_current = periodic_rage_base;

    warr->gain_rage(immediate_rage_gain);
}

void Bloodrage::perform_periodic() {
    // TODO: Add statistics for periodic rage gain.
    warr->gain_rage(1);
    --periodic_rage_current;

    if (periodic_rage_current == 0)
        return;

    auto* new_event = new ResourceGain(pchar, this, engine->get_current_priority() + 1.0);
    this->engine->add_event(new_event);
}
