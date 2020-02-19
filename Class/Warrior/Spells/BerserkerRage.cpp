#include "BerserkerRage.h"

#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "StatisticsResource.h"
#include "Warrior.h"

BerserkerRage::BerserkerRage(Warrior* warrior) :
    Spell("Berserker Rage",
          "Assets/spell/Spell_nature_ancestralguardian.png",
          warrior,
          new CooldownControl(warrior, 30.0),
          RestrictedByGcd::No,
          ResourceType::Rage,
          0),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Improved Berserker Rage", 2, DisabledAtZero::No)}),
    warrior(warrior),
    statistics_resource(nullptr),
    talent_ranks({0, 5, 10}) {}

SpellStatus BerserkerRage::is_ready_spell_specific() const {
    if (warrior->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warrior->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    return SpellStatus::Available;
}

BerserkerRage::~BerserkerRage() {
    delete cooldown;
}

void BerserkerRage::spell_effect() {
    cooldown->add_spell_cd_event();

    unsigned rage_before_gain = warrior->get_resource_level(ResourceType::Rage);
    warrior->gain_rage(rage_gain);
    unsigned delta = warrior->get_resource_level(ResourceType::Rage) - rage_before_gain;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, rage_gain);
}

void BerserkerRage::increase_talent_rank_effect(const QString&, const int curr) {
    rage_gain = talent_ranks[curr];
}

void BerserkerRage::decrease_talent_rank_effect(const QString&, const int curr) {
    rage_gain = talent_ranks[curr];
}

void BerserkerRage::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);
}
