#include "Maul.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "MainhandAttackDruid.h"
#include "NoEffectSelfBuff.h"
#include "SimSettings.h"

Maul::Maul(Druid* druid, DruidSpells* spells, Buff* maul_buff, const int rank_spell) :
    Spell("Maul",
          "Assets/ability/Ability_druid_maul.png",
          druid,
          new CooldownControl(druid, 0.0),
          RestrictedByGcd::No,
          ResourceType::Rage,
          15,
          rank_spell),
    TalentRequirer(QVector<TalentRequirerInfo*> {
        new TalentRequirerInfo("Ferocity", 5, DisabledAtZero::No),
        new TalentRequirerInfo("Savage Fury", 2, DisabledAtZero::No),
    }),
    drood(druid),
    spells(spells),
    maul_buff(maul_buff) {
    damage_mod = 1.0;
    switch (spell_rank) {
    case 1:
        additional_dmg = 18;
        level_req = 10;
        break;
    case 2:
        additional_dmg = 27;
        level_req = 18;
        break;
    case 3:
        additional_dmg = 37;
        level_req = 26;
        break;
    case 4:
        additional_dmg = 49;
        level_req = 34;
        break;
    case 5:
        additional_dmg = 71;
        level_req = 42;
        break;
    case 6:
        additional_dmg = 101;
        level_req = 50;
        break;
    case 7:
        additional_dmg = 128;
        level_req = 58;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }
}

SpellStatus Maul::is_ready_spell_specific() const {
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

Maul::~Maul() {
    delete cooldown;
}

bool Maul::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 7)
        return pchar->get_clvl() >= level_req;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

bool Maul::is_queued() const {
    return maul_buff->is_active();
}

void Maul::cancel() {
    maul_buff->cancel_buff();
}

void Maul::calculate_damage() {
    drood->get_spells()->get_mh_attack()->complete_swing();

    const int result = roll->get_melee_ability_result(drood->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cancel();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        drood->lose_rage(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        drood->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        drood->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    drood->lose_rage(resource_cost);

    double damage_dealt = damage_mod * damage_after_modifiers(drood->get_random_non_normalized_mh_dmg() + additional_dmg);

    if (result == PhysicalAttackResult::CRITICAL) {
        drood->melee_mh_yellow_critical_effect();
        double crit_damage_dealt = damage_dealt * drood->get_stats()->get_melee_ability_crit_dmg_mod();
        add_crit_dmg(static_cast<int>(round(crit_damage_dealt)), resource_cost, 0, round(crit_damage_dealt * 0.75));
    } else if (result == PhysicalAttackResult::HIT) {
        drood->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, 0, round(damage_dealt * 0.75));
    }
}

void Maul::spell_effect() {
    maul_buff->apply_buff();
    is_queued();
}

void Maul::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Ferocity")
        resource_cost = ferocity_ranks[curr];
    else if (talent_name == "Savage Fury")
        damage_mod = 1 + (curr * 0.1);
}

void Maul::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Ferocity")
        resource_cost = ferocity_ranks[curr];
    else if (talent_name == "Savage Fury")
        damage_mod = 1 + (curr * 0.1);
}
