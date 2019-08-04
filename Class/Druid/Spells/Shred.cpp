#include "Shred.h"

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

Shred::Shred(Druid* pchar, DruidSpells* druid_spells, Proc* blood_frenzy, const int spell_rank) :
    Spell("Shred", "Assets/spell/Spell_shadow_vampiricaura.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Energy, 60, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Shred", 2, DisabledAtZero::No),
                   }),
    druid(pchar),
    druid_spells(druid_spells),
    blood_frenzy(blood_frenzy)
{
    switch (spell_rank) {
    case 1:
        bonus_damage = 54;
        level_req = 22;
        break;
    case 2:
        bonus_damage = 72;
        level_req = 30;
        break;
    case 3:
        bonus_damage = 99;
        level_req = 38;
        break;
    case 4:
        bonus_damage = 144;
        level_req = 46;
        break;
    case 5:
        bonus_damage = 180;
        level_req = 54;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }
}

Shred::~Shred() {
    delete cooldown;
}

bool Shred::is_rank_learned() const {
    return pchar->get_clvl() >= level_req;
}

void Shred::spell_effect() {
    druid->exit_stealth();

    const int result = roll->get_melee_ability_result(druid->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        druid->lose_energy(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        druid->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        druid->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    druid->lose_energy(resource_cost);
    druid->gain_combo_points(1);

    double damage_dealt = damage_after_modifiers(druid->get_random_non_normalized_mh_dmg() * 2.25 + bonus_damage);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * druid->get_stats()->get_melee_ability_crit_dmg_mod());
        druid->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());

        if (blood_frenzy->is_enabled() && blood_frenzy->check_proc_success())
            blood_frenzy->perform();
    }
    else if (result == PhysicalAttackResult::HIT) {
        druid->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
}

SpellStatus Shred::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Cat)
        return SpellStatus::Available;

    switch (druid->get_current_form()) {
    case DruidForm::Bear:
        return SpellStatus::InBearForm;
    case DruidForm::Caster:
        return SpellStatus::InCasterForm;
    case DruidForm::Moonkin:
        return SpellStatus::InMoonkinForm;
    default:
        check(false, "Reached end of switch in Shred::is_ready_spell_specific()");
        return SpellStatus::NotEnabled;
    }
}

void Shred::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Shred")
        resource_cost = base_resource_cost - improved_shred_ranks[curr];
}

void Shred::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
