#include "Revenge.h"

#include "Buff.h"
#include "CastComplete.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "HeroicStrike.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "Random.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Revenge::Revenge(Warrior* pchar, WarriorSpells* spells, CooldownControl* cooldown_control) :
    Spell("Revenge", "Assets/ability/Ability_warrior_revenge.png", pchar, cooldown_control, RestrictedByGcd::Yes, ResourceType::Rage, 5),
    warr(pchar),
    spells(spells),
    innate_threat_by_spell_rank({155, 195, 235, 275, 315, 355}),
    innate_threat(315) {
    this->damage_range = new Random(64, 78);
}

Revenge::~Revenge() {
    delete damage_range;
}

SpellStatus Revenge::is_ready_spell_specific() const {
    if (warr->in_battle_stance())
        return SpellStatus::InBattleStance;
    if (warr->in_berserker_stance())
        return SpellStatus::InBerserkerStance;
    // NYI -- revenge as a buff requires implementing incoming damage
    // if (!spells->get_revenge_buff()->is_active())
    //     return SpellStatus::BuffInactive;

    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void Revenge::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    /* spells->get_revenge_buff()->cancel_buff(); */
    cooldown->add_gcd_event();
    cooldown->add_spell_cd_event();

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

    double damage_dealt = damage_after_modifiers(damage_range->get_roll());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown(), innate_threat);
    } else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown(), innate_threat);
    }
}
