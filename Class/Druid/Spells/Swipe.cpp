#include "Swipe.h"

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Proc.h"
#include "SimSettings.h"
#include "Utils/Check.h"

Swipe::Swipe(Druid* pchar, DruidSpells* druid_spells, Proc* primal_fury, const int spell_rank) :
    Spell("Swipe",
          "Assets/ability/Ability_druid_swipe.png",
          pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Rage,
          20,
          spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*> {
        new TalentRequirerInfo("Ferocity", 5, DisabledAtZero::No),
        new TalentRequirerInfo("Savage Fury", 2, DisabledAtZero::No),
    }),
    druid(pchar),
    druid_spells(druid_spells),
    primal_fury(primal_fury) {
    damage_mod = 1.0;
    switch (spell_rank) {
    case 1:
        bonus_damage = 18;
        level_req = 16;
        break;
    case 2:
        bonus_damage = 25;
        level_req = 24;
        break;
    case 3:
        bonus_damage = 36;
        level_req = 34;
        break;
    case 4:
        bonus_damage = 60;
        level_req = 44;
        break;
    case 5:
        bonus_damage = 83;
        level_req = 54;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }
}

Swipe::~Swipe() {
    delete cooldown;
}

bool Swipe::is_rank_learned() const {
    return pchar->get_clvl() >= level_req;
}

void Swipe::spell_effect() {
    druid->exit_stealth();

    const int result = roll->get_melee_ability_result(druid->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        return;
    }

    druid->lose_rage(resource_cost);

    double damage_dealt = damage_mod * damage_after_modifiers(bonus_damage);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * druid->get_stats()->get_melee_ability_crit_dmg_mod());
        druid->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown(), round(damage_dealt * 0.75));

        if (primal_fury->is_enabled() && primal_fury->check_proc_success())
            primal_fury->perform();
    } else if (result == PhysicalAttackResult::HIT) {
        druid->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown(), round(damage_dealt * 0.75));
    }
}

SpellStatus Swipe::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Bear)
        return SpellStatus::Available;

    switch (druid->get_current_form()) {
    case DruidForm::Cat:
        return SpellStatus::InCatForm;
    case DruidForm::Caster:
        return SpellStatus::InCasterForm;
    case DruidForm::Moonkin:
        return SpellStatus::InMoonkinForm;
    default:
        check(false, "Reached end of switch in Swipe::is_ready_spell_specific()");
        return SpellStatus::NotEnabled;
    }
}

void Swipe::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Ferocity")
        resource_cost = base_resource_cost - ferocity_ranks[curr];
    else if (talent_name == "Savage Fury")
        damage_mod = 1 + (curr * 0.1);
}

void Swipe::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Ferocity")
        increase_talent_rank_effect(talent_name, curr);
    else if (talent_name == "Savage Fury")
        damage_mod = 1 + (curr * 0.1);
}
