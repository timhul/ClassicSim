
#include "Character.h"
#include "ClassStatistics.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "EncounterEnd.h"
#include "EncounterStart.h"
#include "SimControl.h"
#include <QDebug>

SimControl::SimControl(SimSettings* sim_settings) :
    sim_settings(sim_settings)
{}

void SimControl::run_quick_sim(Character* pchar) {
    run_sim(pchar);
}

void SimControl::run_full_sim(Character* pchar) {
    run_sim(pchar);
    // do some statistics handling

    QSet<SimOption> options = sim_settings->get_active_options();
    for (auto & option : options) {
        run_sim_with_option(pchar, option);
        // do some statistics handling
    }
}

void SimControl::run_sim(Character* pchar) {
    pchar->get_statistics()->reset_statistics();
    pchar->get_engine()->prepare();
    pchar->get_combat_roll()->drop_tables();

    for (int i = 0; i < sim_settings->get_combat_iterations(); ++i) {
        auto* start_event = new EncounterStart(pchar);
        auto* end_event = new EncounterEnd(pchar->get_engine(), pchar, sim_settings->get_combat_length());

        pchar->get_engine()->add_event(end_event);
        pchar->get_engine()->add_event(start_event);
        pchar->get_engine()->run();
    }

    pchar->get_engine()->reset();
}

void SimControl::run_sim_with_option(Character* pchar, SimOption option) {
    add_option(pchar, option);

    run_sim(pchar);

    remove_option(pchar, option);
}

void SimControl::add_option(Character* pchar, SimOption option) {
    switch (option) {
    case SimOption::ScaleAgility:
        pchar->get_stats()->increase_agility(10);
        break;
    case SimOption::ScaleIntellect:
        pchar->get_stats()->increase_intellect(10);
        break;
    case SimOption::ScaleStrength:
        pchar->get_stats()->increase_strength(10);
        break;
    case SimOption::ScaleMeleeAP:
        pchar->get_stats()->increase_melee_ap(10);
        break;
    case SimOption::ScaleHitChance:
        pchar->get_stats()->increase_hit(0.01);
        break;
    case SimOption::ScaleCritChance:
        pchar->get_stats()->increase_crit(0.01);
        break;
    default:
        qDebug() << "SimControl::add_option unhandled option" << option;
    }
}

void SimControl::remove_option(Character* pchar, SimOption option) {
    switch (option) {
    case SimOption::ScaleAgility:
        pchar->get_stats()->decrease_agility(10);
        break;
    case SimOption::ScaleIntellect:
        pchar->get_stats()->decrease_intellect(10);
        break;
    case SimOption::ScaleStrength:
        pchar->get_stats()->decrease_strength(10);
        break;
    case SimOption::ScaleMeleeAP:
        pchar->get_stats()->decrease_melee_ap(10);
        break;
    case SimOption::ScaleHitChance:
        pchar->get_stats()->decrease_hit(0.01);
        break;
    case SimOption::ScaleCritChance:
        pchar->get_stats()->decrease_crit(0.01);
        break;
    default:
        qDebug() << "SimControl::remove_option unhandled option" << option;
    }
}
