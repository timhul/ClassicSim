#include "SimulationThreadPool.h"

#include <climits>

#include <QDebug>
#include <QThread>

#include "Random.h"
#include "SimSettings.h"
#include "SimulationRunner.h"
#include "Utils/Check.h"

SimulationThreadPool::SimulationThreadPool(
    EquipmentDb* equipment_db, RandomAffixes* random_affixes, SimSettings* sim_settings, NumberCruncher* scaler, QObject* parent) :
    QObject(parent),
    equipment_db(equipment_db),
    random_affixes(random_affixes),
    random(new Random(0, std::numeric_limits<unsigned>::max())),
    sim_settings(sim_settings),
    scaler(scaler),
    running_threads(0) {
    for (int i = 0; i < sim_settings->get_num_threads_current(); ++i) {
        setup_thread(random->get_roll());
    }
}

SimulationThreadPool::~SimulationThreadPool() {
    delete random;
    for (const auto& thread_entry : thread_pool)
        delete thread_entry.second;
}

void SimulationThreadPool::run_sim(const QVector<QString>& setup_string, bool full_sim, int iterations, const int num_options) {
    check((running_threads == 0), "Cannot run sim while threads are still running");
    max_iterations = iterations * num_options;
    iterations_completed = 0;

    auto iterations_per_thread = static_cast<int>(static_cast<double>(iterations) / active_thread_ids.size());

    for (const auto& thread : thread_pool) {
        if (!active_thread_ids.contains(thread.first))
            continue;

        emit start_simulation(thread.first, setup_string, full_sim, iterations_per_thread);
        ++running_threads;
    }

    check((running_threads > 0), "Failed to start threads");
}

bool SimulationThreadPool::sim_running() const {
    return running_threads > 0;
}

void SimulationThreadPool::scale_number_of_threads() {
    if (sim_running())
        return;

    int thread_diff = sim_settings->get_num_threads_current() - active_thread_ids.size();

    if (thread_diff == 0)
        return;

    if (thread_diff < 0)
        remove_threads(-thread_diff);
    else
        add_threads(thread_diff);

    check((active_thread_ids.size() == sim_settings->get_num_threads_current()), "Failed to scale number of threads");
}

void SimulationThreadPool::add_threads(const int num_to_add) {
    for (int i = 0; i < num_to_add; ++i) {
        if (inactive_thread_ids.empty())
            setup_thread(random->get_roll());
        else {
            active_thread_ids.append(inactive_thread_ids.takeLast());
        }
    }
}

void SimulationThreadPool::remove_threads(const int num_to_remove) {
    check((num_to_remove < active_thread_ids.size()), "Must not remove all threads");

    for (int i = 0; i < num_to_remove; ++i) {
        inactive_thread_ids.append(active_thread_ids.takeLast());
    }

    check(!active_thread_ids.empty(), "All threads were removed in previous operation");
}

void SimulationThreadPool::setup_thread(const unsigned thread_id) {
    auto runner = new SimulationRunner(thread_id, equipment_db, random_affixes, sim_settings, scaler);
    auto thread = new QThread(runner);

    connect(this, SIGNAL(start_simulation(uint, QVector<QString>, bool, int)), runner, SLOT(sim_runner_run(uint, QVector<QString>, bool, int)));
    connect(runner, SIGNAL(error(QString, QString)), this, SLOT(error_string(QString, QString)));
    connect(runner, SIGNAL(simulation_runner_has_result()), this, SLOT(thread_finished()));
    connect(runner, SIGNAL(update_progress(const int)), this, SLOT(increase_iterations_completed(int)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread_pool.append(QPair<unsigned, QThread*>(thread_id, thread));
    active_thread_ids.append(thread_id);

    runner->moveToThread(thread);
    thread->start();
}

void SimulationThreadPool::error_string(const QString& seed, const QString& error) {
    qDebug() << "thread error" << seed << ": " << error;
    thread_finished();
}

void SimulationThreadPool::thread_finished() {
    --running_threads;

    if (running_threads > 0)
        return;

    emit threads_finished();
}

void SimulationThreadPool::increase_iterations_completed(int iterations) {
    iterations_completed += iterations;
    emit update_progress(static_cast<double>(iterations_completed) / max_iterations);
}
