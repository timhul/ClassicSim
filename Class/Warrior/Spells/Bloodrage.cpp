#include "Bloodrage.h"

#include "Buff.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "StatisticsResource.h"
#include "Warrior.h"

Bloodrage::Bloodrage(Character* pchar) :
    PeriodicResourceGainSpell("Bloodrage", "Assets/ability/Ability_racial_bloodrage.png", pchar, RestrictedByGcd::No, 1.0, 10, {{ResourceType::Rage, 1}}),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Bloodrage", 2, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    delete cooldown;
    cooldown = new CooldownControl(pchar, 60.0);
    enabled = true;
    marker_buff->enable_buff();
}

void Bloodrage::new_application_effect() {
    cooldown->add_spell_cd_event();

    gain_rage(immediate_rage_gain);
}

SpellStatus Bloodrage::is_ready_spell_specific() const {
    return warr->in_defensive_stance() ? SpellStatus::InDefensiveStance : SpellStatus::Available;
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
