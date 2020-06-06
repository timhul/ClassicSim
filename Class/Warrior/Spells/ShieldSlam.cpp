#include "ShieldSlam.h"

#include <cmath>

#include "Buff.h"
#include "CastComplete.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Equipment.h"
#include "HeroicStrike.h"
#include "Item.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "Random.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Weapon.h"

ShieldSlam::ShieldSlam(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control) :
    Spell("Shield Slam", "Assets/ability/Ability_warrior_sunder.png", pchar, cooldown_control, RestrictedByGcd::Yes, ResourceType::Rage, 20),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo("Shield Slam", 1, DisabledAtZero::Yes)}),
    warr(pchar),
    spells(spells),
    innate_threat(250) {
    this->damage_range = new Random(342, 358);
    this->enabled = false;
}

ShieldSlam::~ShieldSlam() {
    delete damage_range;
}

void ShieldSlam::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_spell_cd_event();
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

    auto stats = warr->get_stats();
    auto strength = stats->get_strength();
    auto strength_to_block_value = std::round(strength / 20);
    auto block_value = stats->get_block_value();
    double damage_dealt = damage_after_modifiers(damage_range->get_roll() + strength_to_block_value + block_value);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown(), 250);
    } else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown(), 250);
    }
}

SpellStatus ShieldSlam::is_ready_spell_specific() const {
    auto offhand = warr->get_equipment()->get_offhand();
    if (offhand && offhand->get_weapon_type() != WeaponTypes::SHIELD)
        return SpellStatus::IncorrectWeaponType;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void ShieldSlam::increase_talent_rank_effect(const QString&, const int) {}

void ShieldSlam::decrease_talent_rank_effect(const QString&, const int) {}
