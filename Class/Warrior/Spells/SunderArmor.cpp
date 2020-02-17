#include "SunderArmor.h"

#include "Buff.h"
#include "CastComplete.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "HeroicStrike.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "Warrior.h"
#include "WarriorSpells.h"

SunderArmor::SunderArmor(Warrior* pchar, WarriorSpells* spells) :
    Spell("Sunder Armor",
          "Assets/ability/Ability_warrior_sunder.png",
          pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Rage,
          15),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Improved Sunder Armor", 3, DisabledAtZero::No)}),
    warr(pchar),
    spells(spells),
    // TODO find these lower level values
    innate_threat_by_spell_rank({0, 0, 0, 0, 260}),
    innate_threat(260),
    talent_ranks({15, 14, 13, 12}) {}

SunderArmor::~SunderArmor() {
    delete cooldown;
}

void SunderArmor::increase_talent_rank_effect(const QString&, const int curr) {
    resource_cost = talent_ranks[curr];
}

void SunderArmor::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = talent_ranks[curr];
}

SpellStatus SunderArmor::is_ready_spell_specific() const {
    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void SunderArmor::spell_effect() {
    // Sunder armor can't crit
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), 0);

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        warr->lose_rage(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        spells->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    warr->lose_rage(resource_cost);
    warr->melee_mh_yellow_hit_effect();
}
