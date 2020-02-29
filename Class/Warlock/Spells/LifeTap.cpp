#include "LifeTap.h"

#include <cmath>

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "SimSettings.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"
#include "Warlock.h"
#include "WarlockSpells.h"

LifeTap::LifeTap(Warlock* warlock, WarlockSpells* warlock_spells, const int spell_rank_) :
    Spell("Life Tap",
          "Assets/spell/Spell_shadow_burningspirit.png",
          warlock,
          new CooldownControl(warlock, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          0,
          spell_rank_),
    TalentRequirer(QVector<TalentRequirerInfo*> {
        new TalentRequirerInfo("Improved Life Tap", 2, DisabledAtZero::No),
    }),
    warlock_spells(warlock_spells) {
    switch (spell_rank) {
    case 1:
        base_resource_yield = 30;
        level_req = 1;
        break;
    case 2:
        base_resource_yield = 75;
        level_req = 6;
        break;
    case 3:
        base_resource_yield = 140;
        level_req = 12;
        break;
    case 4:
        base_resource_yield = 220;
        level_req = 20;
        break;
    case 5:
        base_resource_yield = 310;
        level_req = 28;
        break;
    case 6:
        base_resource_yield = 424;
        level_req = 36;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    resource_yield = base_resource_yield;
}

LifeTap::~LifeTap() {
    delete cooldown;
}

bool LifeTap::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 6)
        return pchar->get_clvl() >= level_req;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void LifeTap::spell_effect() {
    cooldown->add_gcd_event();

    const unsigned before_gain = pchar->get_resource_level(ResourceType::Mana);

    // TODO: Target should not be a part of this spell power calculation at all, regardless of ConsumeCharge::No. Improve this handling.
    const unsigned spell_power_including_target = pchar->get_stats()->get_spell_damage(MagicSchool::Shadow, ConsumeCharge::No);
    const double spell_power_bonus = spell_dmg_coefficient
                                     * (spell_power_including_target - pchar->get_target()->get_spell_damage(MagicSchool::Shadow, ConsumeCharge::No));
    const unsigned modified_yield = static_cast<unsigned>(std::round(imp_life_tap * (resource_yield + spell_power_bonus)));

    pchar->gain_mana(modified_yield);
    const unsigned delta = pchar->get_resource_level(ResourceType::Mana) - before_gain;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

void LifeTap::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(QString("%1 (rank %2)").arg(name).arg(spell_rank), icon);
}

void LifeTap::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Life Tap")
        imp_life_tap = imp_life_tap_ranks[curr];
}

void LifeTap::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
