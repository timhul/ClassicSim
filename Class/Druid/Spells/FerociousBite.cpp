#include "FerociousBite.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "Equipment.h"
#include "Random.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Weapon.h"

FerociousBite::FerociousBite(Druid* druid, const int spell_rank_) :
    Spell("Ferocious Bite", "Assets/ability/Ability_druid_ferociousbite.png", druid, new CooldownControl(druid, 0.0), RestrictedByGcd::Yes, ResourceType::Energy, 35, spell_rank_),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Feral Aggression", 5, DisabledAtZero::No),
                   }),
    druid(druid),
    instant_dmg(new Random(1, 1))
{
    switch (spell_rank_) {
    case 1:
        damage_ranges_per_combo_point = {
            QPair<unsigned, unsigned>(50, 66),
            QPair<unsigned, unsigned>(86, 102),
            QPair<unsigned, unsigned>(122, 138),
            QPair<unsigned, unsigned>(158, 174),
            QPair<unsigned, unsigned>(194, 210),
        };
        bonus_dmg_per_energy_converted = 1.0;
        level_req = 32;
        break;
    case 2:
        damage_ranges_per_combo_point = {
            QPair<unsigned, unsigned>(79, 103),
            QPair<unsigned, unsigned>(138, 162),
            QPair<unsigned, unsigned>(197, 221),
            QPair<unsigned, unsigned>(256, 280),
            QPair<unsigned, unsigned>(315, 339),
        };
        bonus_dmg_per_energy_converted = 1.5;
        level_req = 40;
        break;
    case 3:
        damage_ranges_per_combo_point = {
            QPair<unsigned, unsigned>(122, 162),
            QPair<unsigned, unsigned>(214, 254),
            QPair<unsigned, unsigned>(306, 346),
            QPair<unsigned, unsigned>(398, 438),
            QPair<unsigned, unsigned>(490, 530),
        };
        bonus_dmg_per_energy_converted = 2.0;
        level_req = 48;
        break;
    case 4:
        damage_ranges_per_combo_point = {
            QPair<unsigned, unsigned>(173, 223),
            QPair<unsigned, unsigned>(301, 351),
            QPair<unsigned, unsigned>(429, 479),
            QPair<unsigned, unsigned>(557, 607),
            QPair<unsigned, unsigned>(685, 735),
        };
        bonus_dmg_per_energy_converted = 2.5;
        level_req = 56;
        break;
    case 5:
        damage_ranges_per_combo_point = {
            QPair<unsigned, unsigned>(199, 259),
            QPair<unsigned, unsigned>(346, 406),
            QPair<unsigned, unsigned>(493, 553),
            QPair<unsigned, unsigned>(640, 700),
            QPair<unsigned, unsigned>(787, 847),
        };
        bonus_dmg_per_energy_converted = 2.7;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank_).toStdString());
    }
}

FerociousBite::~FerociousBite() {
    delete instant_dmg;
    delete cooldown;
}

SpellStatus FerociousBite::is_ready_spell_specific() const {
    switch (druid->get_current_form()) {
    case DruidForm::Bear:
        return SpellStatus::InBearForm;
    case DruidForm::Caster:
        return SpellStatus::InCasterForm;
    case DruidForm::Moonkin:
        return SpellStatus::InMoonkinForm;
    case DruidForm::Cat:
        break;
    }

    return druid->get_combo_points() > 0 ? SpellStatus::Available : SpellStatus::InsufficientComboPoints;
}

bool FerociousBite::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 4)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 5)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 5;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void FerociousBite::spell_effect() {
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

    set_combo_point_damage_range();
    const double ap_modifier = druid->get_stats()->get_melee_ap() * (druid->get_combo_points() * 0.03);
    const unsigned energy_level = druid->get_resource_level(ResourceType::Energy);
    const double bonus_from_converted_energy = (energy_level - resource_cost) * bonus_dmg_per_energy_converted;
    double damage_dealt = damage_after_modifiers((instant_dmg->get_roll() + ap_modifier + bonus_from_converted_energy) * feral_aggression_modifier);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= round(druid->get_stats()->get_melee_ability_crit_dmg_mod());
        druid->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        druid->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    druid->lose_energy(energy_level);
    druid->spend_combo_points();
}

void FerociousBite::set_combo_point_damage_range() {
    const int index = static_cast<int>(druid->get_combo_points()) - 1;
    check((index >= 0 && index <= damage_ranges_per_combo_point.size() -1), "Index out of range");

    const unsigned min = damage_ranges_per_combo_point[index].first;
    const unsigned max = damage_ranges_per_combo_point[index].second;

    instant_dmg->set_new_range(min, max);
}

void FerociousBite::increase_talent_rank_effect(const QString&, const int curr) {
    feral_aggression_modifier = feral_aggression_modifiers[curr];
}

void FerociousBite::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
