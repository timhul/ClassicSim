#include "SimulationRunner.h"

#include <utility>

#include <QVersionNumber>

#include "Character.h"
#include "CharacterDecoder.h"
#include "CharacterEncoder.h"
#include "CharacterLoader.h"
#include "CombatRoll.h"
#include "Race.h"
#include "RaidControl.h"
#include "Random.h"
#include "SimControl.h"
#include "SimSettings.h"

SimulationRunner::SimulationRunner(
    unsigned thread_id, EquipmentDb* equipment_db, RandomAffixes* random_affixes, SimSettings* sim_settings, NumberCruncher* scaler, QObject* parent) :
    QObject(parent),
    equipment_db(equipment_db),
    random_affixes(random_affixes),
    global_sim_settings(sim_settings),
    local_sim_settings(nullptr),
    scaler(scaler),
    full_sim(false),
    thread_id(thread_id) {}

void SimulationRunner::sim_runner_run(unsigned thread_id, QVector<QString> setup_strings, bool full_sim, int iterations) {
    if (this->thread_id != thread_id) {
        emit finished();
        return;
    }

    this->setup_strings = std::move(setup_strings);
    this->full_sim = full_sim;

    CharacterDecoder decoder(this->setup_strings[0]);

    this->local_sim_settings = new SimSettings();
    local_sim_settings->set_phase(Content::get_phase(decoder.get_value("PHASE").toInt()));
    local_sim_settings->set_combat_iterations_full_sim(iterations);
    local_sim_settings->set_combat_iterations_quick_sim(iterations);
    local_sim_settings->set_sim_options(global_sim_settings->get_active_options());
    local_sim_settings->set_combat_length(global_sim_settings->get_combat_length());

    raid_control = new RaidControl(local_sim_settings);

    Random pchar_seeds(0, std::numeric_limits<unsigned>::max());

    for (const auto& setup_string : this->setup_strings) {
        CharacterDecoder decoder_pchar(setup_string);
        CharacterLoader loader(equipment_db, random_affixes, local_sim_settings, raid_control, decoder_pchar);
        raid.append(loader.initialize_new());

        if (!loader.successful())
            exit_thread(loader.get_error());

        races.append(loader.relinquish_ownership_of_race());

        CharacterEncoder encoder(raid.last());
        if (encoder.get_current_setup_string() != setup_string)
            return exit_thread("Mismatch between setup strings after setup: dumped setup string: " + encoder.get_current_setup_string());

        raid.last()->get_combat_roll()->set_new_seed(pchar_seeds.get_roll());
    }

    SimControl sim_control(local_sim_settings, scaler);
    QObject::connect(&sim_control, &SimControl::update_progress, this, &SimulationRunner::receive_progress);

    if (full_sim)
        sim_control.run_full_sim(raid, raid_control);
    else
        sim_control.run_quick_sim(raid, raid_control);

    for (const auto& pchar : raid)
        delete pchar;
    for (const auto& race : races)
        delete race;

    raid.clear();
    races.clear();

    delete local_sim_settings;
    delete raid_control;

    emit simulation_runner_has_result();
    emit finished();
}

void SimulationRunner::receive_progress(const int iterations_completed) {
    emit update_progress(iterations_completed);
}

void SimulationRunner::exit_thread(QString err) {
    for (const auto& pchar : raid)
        delete pchar;
    for (const auto& race : races)
        delete race;

    delete local_sim_settings;
    delete raid_control;
    emit error(QString::number(thread_id), std::move(err));
    emit finished();
}
