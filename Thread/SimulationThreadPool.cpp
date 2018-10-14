
#include "SimulationThreadPool.h"
#include "SimulationRunner.h"
#include "Random.h"
#include <climits>
#include <QThread>
#include <QDebug>
#include <QThreadPool>

SimulationThreadPool::SimulationThreadPool(EquipmentDb* equipment_db, SimSettings* sim_settings, NumberCruncher* scaler, QObject* parent):
    QObject(parent),
    equipment_db(equipment_db),
    random(new Random(0, std::numeric_limits<unsigned>::max())),
    sim_settings(sim_settings),
    scaler(scaler),
    running_threads(0)
{
    for (int i = 0; i < QThreadPool::globalInstance()->maxThreadCount(); ++i) {
        setup_thread(random->get_roll());
    }
}

SimulationThreadPool::~SimulationThreadPool() {
    delete random;
    for (auto & thread_entry : thread_pool)
        delete thread_entry.second;
}

void SimulationThreadPool::run_sim(const QString &setup_string, bool full_sim) {
    assert(running_threads == 0);
    assert(thread_results.empty());

    for (auto & i : thread_pool) {
        thread_results.append(QPair<unsigned, double>(i.first, 0.0));
    }

    running_threads = thread_pool.size();
    emit thread_setup_string(setup_string, full_sim);
}

void SimulationThreadPool::setup_thread(const unsigned thread_id) {
    auto* thread = new QThread();
    SimulationRunner* runner = new SimulationRunner(equipment_db, sim_settings, scaler, QString::number(thread_id));

    connect(this, SIGNAL (thread_setup_string(QString, bool)), runner, SLOT (run_sim(QString, bool)));
    connect(runner, SIGNAL (error(QString, QString)), this, SLOT (error_string(QString, QString)));
    connect(runner, SIGNAL (result(QString, double)), this, SLOT (result(QString, double)));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));

    thread_pool.append(QPair<unsigned, QThread*>(thread_id, thread));

    runner->moveToThread(thread);
    thread->start();
}

void SimulationThreadPool::error_string(const QString& seed, const QString& error) {
    qDebug() << "thread error" << seed << ": " << error;
    --running_threads;

    if (running_threads == 0) {
        thread_results.clear();
    }
}

void SimulationThreadPool::result(const QString& seed, double result) {
    --running_threads;

    for (auto & thread_result : thread_results) {
        if (thread_result.first != seed.toUInt())
            continue;

        thread_result.second = result;
    }

    check_threads_finished();
}

void SimulationThreadPool::check_threads_finished() {
    if (running_threads == 0) {
        double avg_dps = 0.0;
        int num_threads_with_result = 0;

        for (auto & thread_result : thread_results) {
            if (thread_result.second < 0.001)
                continue;

            ++num_threads_with_result;
            avg_dps += thread_result.second;
            if (num_threads_with_result > 1)
                avg_dps /= 2;
        }

        QString avg_dps_string = QString::number(avg_dps, 'f', 2);
        qDebug() << QString("Average dps from %1 threads: %2").arg(QString::number(num_threads_with_result), avg_dps_string);
        threads_finished();
        thread_results.clear();
    }
}
