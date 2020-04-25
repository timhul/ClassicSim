#include "Enrage.h"

#include "Buff.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "StatisticsResource.h"
#include "Druid.h"
#include "Utils/Check.h"

Enrage::Enrage(Druid* druid) :
    PeriodicResourceGainSpell("Enrage",
                              "Assets/ability/Ability_druid_enrage.png",
                              druid,
                              RestrictedByGcd::No,
                              1.0,
                              10,
                              {{ResourceType::Rage, 2}}),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Improved Enrage", 2, DisabledAtZero::No)}),
    drood(druid) {
    delete cooldown;
    cooldown = new CooldownControl(druid, 60.0);
    enabled = true;
    marker_buff->enable_buff();
}

void Enrage::new_application_effect() {
    cooldown->add_spell_cd_event();

    gain_rage(immediate_rage_gain);
}

SpellStatus Enrage::is_ready_spell_specific() const {
    if (drood->get_current_form() == DruidForm::Bear)
        return SpellStatus::Available;

    switch (drood->get_current_form()) {
    case DruidForm::Cat:
        return SpellStatus::InCatForm;
    case DruidForm::Caster:
        return SpellStatus::InCasterForm;
    case DruidForm::Moonkin:
        return SpellStatus::InMoonkinForm;
    default:
        check(false, "Reached end of switch in Shred::is_ready_spell_specific()");
        return SpellStatus::NotEnabled;
    }
}

void Enrage::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Enrage")
        this->immediate_rage_gain = talent_ranks[curr];
}

void Enrage::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Enrage")
        this->immediate_rage_gain = talent_ranks[curr];
}

void Enrage::gain_rage(const unsigned rage_gain) {
    const unsigned before = drood->get_resource_level(ResourceType::Rage);

    drood->gain_rage(rage_gain);

    const unsigned gain_after_cap = drood->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}
