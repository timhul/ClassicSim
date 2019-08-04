#include "HeroicStrike.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "MainhandAttackWarrior.h"
#include "NoEffectSelfBuff.h"
#include "SimSettings.h"
#include "Warrior.h"
#include "WarriorSpells.h"

HeroicStrike::HeroicStrike(Warrior* pchar, WarriorSpells* spells, Buff* hs_buff, const int spell_rank) :
    Spell("Heroic Strike", "Assets/ability/Ability_rogue_ambush.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::No, ResourceType::Rage, 15, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Heroic Strike", 3, DisabledAtZero::No)}),
    warr(pchar),
    spells(spells),
    hs_buff(hs_buff)
{
    switch (spell_rank) {
    case 1:
        additional_dmg = 11;
        level_req = 1;
        break;
    case 2:
        additional_dmg = 21;
        level_req = 8;
        break;
    case 3:
        additional_dmg = 32;
        level_req = 16;
        break;
    case 4:
        additional_dmg = 44;
        level_req = 24;
        break;
    case 5:
        additional_dmg = 58;
        level_req = 32;
        break;
    case 6:
        additional_dmg = 80;
        level_req = 40;
        break;
    case 7:
        additional_dmg = 111;
        level_req = 48;
        break;
    case 8:
        additional_dmg = 138;
        level_req = 56;
        break;
    case 9:
        additional_dmg = 157;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }
}

HeroicStrike::~HeroicStrike() {
    delete cooldown;
}

bool HeroicStrike::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 8)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 9)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 5;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

bool HeroicStrike::is_queued() const {
    return hs_buff->is_active();
}

void HeroicStrike::cancel() {
    hs_buff->cancel_buff();
}

void HeroicStrike::calculate_damage() {
    hs_buff->cancel_buff();
    warr->get_spells()->get_mh_attack()->complete_swing();

    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

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

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_mh_dmg() + additional_dmg);

    if (result == PhysicalAttackResult::CRITICAL) {
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * warr->get_stats()->get_melee_ability_crit_dmg_mod())), resource_cost, 0);
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0);
    }

    warr->lose_rage(resource_cost);
}

void HeroicStrike::spell_effect() {
    hs_buff->apply_buff();
}

void HeroicStrike::increase_talent_rank_effect(const QString&, const int curr) {
    resource_cost = improved_hs_ranks[curr];
}

void HeroicStrike::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = improved_hs_ranks[curr];
}
