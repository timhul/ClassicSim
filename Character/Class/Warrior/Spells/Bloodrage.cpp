#include "Bloodrage.h"

#include "Engine.h"
#include "ResourceGain.h"
#include "Warrior.h"

Bloodrage::Bloodrage(Character* pchar) :
    Spell("Bloodrage", "Assets/warrior/protection/tier2/Ability_racial_bloodrage.png", pchar, RestrictedByGcd::No, 60, ResourceType::Rage, 0),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Bloodrage", 2, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->talent_ranks = {10, 12, 15};
    this->immediate_rage_gain = talent_ranks[0];
    this->periodic_rage_base = 10;
    this->periodic_rage_current = periodic_rage_base;
}

bool Bloodrage::is_ready_spell_specific() const {
    return !warr->in_defensive_stance();
}

void Bloodrage::increase_talent_rank_effect(const int curr, const QString&) {
    this->immediate_rage_gain = talent_ranks[curr];
}

void Bloodrage::decrease_talent_rank_effect(const int curr, const QString&) {
    this->immediate_rage_gain = talent_ranks[curr];
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
