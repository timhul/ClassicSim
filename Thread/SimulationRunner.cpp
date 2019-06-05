#include "SimulationRunner.h"

#include <QVersionNumber>
#include <utility>

#include "Character.h"
#include "CharacterDecoder.h"
#include "CharacterEncoder.h"
#include "CharacterLoader.h"
#include "CombatRoll.h"
#include "Race.h"
#include "RaidControl.h"
#include "SimControl.h"
#include "SimSettings.h"
#include "Target.h"

SimulationRunner::SimulationRunner(unsigned thread_id, EquipmentDb* equipment_db, SimSettings *sim_settings, NumberCruncher* scaler, QObject* parent):
    QObject(parent),
    pchar(nullptr),
    equipment_db(equipment_db),
    race(nullptr),
    global_sim_settings(sim_settings),
    local_sim_settings(nullptr),
    scaler(scaler),
    full_sim(false),
    thread_id(thread_id)
{}

void SimulationRunner::run_sim(unsigned thread_id, QString setup_string, bool full_sim, int iterations) {
    if (this->thread_id != thread_id) {
        emit finished();
        return;
    }

    this->setup_string = std::move(setup_string);
    this->full_sim = full_sim;

    CharacterDecoder decoder;
    decoder.initialize(this->setup_string);

    this->local_sim_settings = new SimSettings();
    local_sim_settings->set_phase(Content::get_phase(decoder.get_value("PHASE").toInt()));
    local_sim_settings->set_combat_iterations_full_sim(iterations);
    local_sim_settings->set_combat_iterations_quick_sim(iterations);
    local_sim_settings->set_sim_options(global_sim_settings->get_active_options());
    local_sim_settings->set_combat_length(global_sim_settings->get_combat_length());

    target = new Target(63);
    raid_control = new RaidControl(local_sim_settings);

    CharacterLoader loader(equipment_db, local_sim_settings, target, raid_control, decoder);
    pchar = loader.initialize_new();

    if (!loader.successful())
        exit_thread(loader.get_error());

    race = loader.relinquish_ownership_of_race();

    CharacterEncoder encoder(pchar);
    if (encoder.get_current_setup_string() != this->setup_string)
        return exit_thread("Mismatch between setup strings after setup: dumped setup string: " + encoder.get_current_setup_string());

    pchar->get_combat_roll()->set_new_seed(this->thread_id);

    if (full_sim)
        SimControl(local_sim_settings, scaler).run_full_sim(QVector<Character*>{pchar}, raid_control);
    else
        SimControl(local_sim_settings, scaler).run_quick_sim(QVector<Character*>{pchar}, raid_control);

    delete pchar;
    delete race;
    delete local_sim_settings;
    delete target;
    delete raid_control;

    emit result();
    emit finished();
}

void SimulationRunner::exit_thread(QString err) {
    delete pchar;
    delete race;
    delete local_sim_settings;
    delete target;
    delete raid_control;
    emit error(QString::number(thread_id), std::move(err));
    emit finished();
}
