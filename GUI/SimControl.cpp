#include "SimControl.h"

#include <QDebug>

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "EncounterEnd.h"
#include "EncounterStart.h"
#include "Engine.h"
#include "ItemNamespace.h"
#include "NumberCruncher.h"
#include "RaidControl.h"
#include "Rotation.h"
#include "SpellCastingTime.h"

SimControl::SimControl(SimSettings* sim_settings, NumberCruncher *scaler) :
    sim_settings(sim_settings),
    scaler(scaler)
{}

void SimControl::run_quick_sim(QVector<Character*> raid, RaidControl* raid_control) {
    run_sim(raid, raid_control, sim_settings->get_combat_length(), sim_settings->get_combat_iterations_quick_sim());

    for (int i = 1; i < raid.size(); ++i)
        raid[0]->get_statistics()->add_player_dps(raid[i]->get_statistics()->get_total_personal_dps());
    scaler->add_class_statistic(SimOption::Name::NoScale, raid[0]->relinquish_ownership_of_statistics());
    scaler->add_class_statistic(SimOption::Name::NoScale, raid[0]->get_raid_control()->relinquish_ownership_of_statistics());
}

void SimControl::run_full_sim(QVector<Character*> raid, RaidControl* raid_control) {
    run_sim(raid, raid_control, sim_settings->get_combat_length(), sim_settings->get_combat_iterations_full_sim());

    for (int i = 1; i < raid.size(); ++i)
        raid[0]->get_statistics()->add_player_dps(raid[i]->get_statistics()->get_total_personal_dps());
    scaler->add_class_statistic(SimOption::Name::NoScale, raid[0]->relinquish_ownership_of_statistics());
    scaler->add_class_statistic(SimOption::Name::NoScale, raid[0]->get_raid_control()->relinquish_ownership_of_statistics());

    QSet<SimOption::Name> options = sim_settings->get_active_options();
    for (const auto & option : options) {
        qDebug() << "Running sim with option" << option;
        run_sim_with_option(raid, raid_control, option, sim_settings->get_combat_length(), sim_settings->get_combat_iterations_full_sim());

        for (int i = 1; i < raid.size(); ++i)
            raid[0]->get_statistics()->add_player_dps(raid[i]->get_statistics()->get_total_personal_dps());
        scaler->add_class_statistic(option, raid[0]->relinquish_ownership_of_statistics());
        scaler->add_class_statistic(option, raid[0]->get_raid_control()->relinquish_ownership_of_statistics());
    }
}

void SimControl::run_sim(QVector<Character*> raid, RaidControl* raid_control, const int combat_length, const int iterations) {
    raid_control->prepare_set_of_combat_iterations();

    for (const auto & pchar : raid) {
        pchar->get_combat_roll()->drop_tables();
        pchar->prepare_set_of_combat_iterations();
    }

    double start_at = std::numeric_limits<double>::min();
    for (const auto & pchar : raid) {
        const double time_for_precombat = pchar->get_spells()->get_rotation()->get_time_required_to_run_precombat();
        if (time_for_precombat > start_at)
            start_at = time_for_precombat;
    }

    int reported_iterations = 0;
    for (int i = 0; i < iterations; ++i) {
        raid_control->get_engine()->prepare_iteration(-start_at);
        for (const auto & pchar : raid) {
            Rotation* rotation = pchar->get_spells()->get_rotation();
            rotation->run_precombat_actions();
            if (rotation->precast_spell != nullptr && rotation->precast_spell->is_enabled())
                rotation->precast_spell->perform();
        }

        for (const auto & pchar : raid)
            raid_control->get_engine()->add_event(new EncounterStart(pchar->get_spells(), pchar->get_enabled_buffs()));

        raid_control->get_engine()->add_event(new EncounterEnd(raid_control->get_engine(), combat_length));
        raid_control->get_engine()->run();

        raid_control->reset();
        raid_control->get_statistics()->finish_combat_iteration();
        raid_control->get_target()->reset();

        for (const auto & pchar : raid) {
            pchar->reset();
            pchar->get_statistics()->finish_combat_iteration();
        }

        ++reported_iterations;
        if (reported_iterations % 10 == 0) {
            emit update_progress(reported_iterations);
            reported_iterations = 0;
        }
    }

    for (const auto & pchar : raid)
        pchar->get_spells()->get_rotation()->finish_set_of_combat_iterations();

    raid_control->get_engine()->reset();
}

void SimControl::run_sim_with_option(QVector<Character*> raid, RaidControl* raid_control, SimOption::Name option, const int combat_length, const int iterations) {
    for (const auto & pchar : raid)
        add_option(pchar, option);

    run_sim(raid, raid_control, combat_length, iterations);

    for (const auto & pchar : raid)
        remove_option(pchar, option);
}

void SimControl::add_option(Character* pchar, SimOption::Name option) {
    switch (option) {
    case SimOption::Name::NoScale:
        break;
    case SimOption::Name::ScaleAgility:
        pchar->get_stats()->increase_agility(10);
        break;
    case SimOption::Name::ScaleStrength:
        pchar->get_stats()->increase_strength(10);
        break;
    case SimOption::Name::ScaleMeleeAP:
        pchar->get_stats()->increase_melee_ap(10);
        break;
    case SimOption::Name::ScaleHitChance:
        pchar->get_stats()->increase_melee_hit(100);
        break;
    case SimOption::Name::ScaleCritChance:
        pchar->get_stats()->increase_melee_crit(100);
        break;
    case SimOption::Name::ScaleAxeSkill:
        pchar->get_stats()->increase_wpn_skill(WeaponTypes::AXE, 1);
        break;
    case SimOption::Name::ScaleDaggerSkill:
        pchar->get_stats()->increase_wpn_skill(WeaponTypes::DAGGER, 1);
        break;
    case SimOption::Name::ScaleMaceSkill:
        pchar->get_stats()->increase_wpn_skill(WeaponTypes::MACE, 1);
        break;
    case SimOption::Name::ScaleSwordSkill:
        pchar->get_stats()->increase_wpn_skill(WeaponTypes::SWORD, 1);
        break;
    }

    pchar->get_statistics()->set_sim_option(option);
}

void SimControl::remove_option(Character* pchar, SimOption::Name option) {
    switch (option) {
    case SimOption::Name::NoScale:
        break;
    case SimOption::Name::ScaleAgility:
        pchar->get_stats()->decrease_agility(10);
        break;
    case SimOption::Name::ScaleStrength:
        pchar->get_stats()->decrease_strength(10);
        break;
    case SimOption::Name::ScaleMeleeAP:
        pchar->get_stats()->decrease_melee_ap(10);
        break;
    case SimOption::Name::ScaleHitChance:
        pchar->get_stats()->decrease_melee_hit(1);
        break;
    case SimOption::Name::ScaleCritChance:
        pchar->get_stats()->decrease_melee_crit(100);
        break;
    case SimOption::Name::ScaleAxeSkill:
        pchar->get_stats()->decrease_wpn_skill(WeaponTypes::AXE, 1);
        break;
    case SimOption::Name::ScaleDaggerSkill:
        pchar->get_stats()->decrease_wpn_skill(WeaponTypes::DAGGER, 1);
        break;
    case SimOption::Name::ScaleMaceSkill:
        pchar->get_stats()->decrease_wpn_skill(WeaponTypes::MACE, 1);
        break;
    case SimOption::Name::ScaleSwordSkill:
        pchar->get_stats()->decrease_wpn_skill(WeaponTypes::SWORD, 1);
        break;
    }
}
