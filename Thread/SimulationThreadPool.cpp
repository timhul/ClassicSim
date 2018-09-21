
#include "SimulationThreadPool.h"
#include "SimulationRunner.h"
#include "Random.h"
#include <limits.h>
#include <QThread>
#include <QDebug>
#include <QThreadPool>

SimulationThreadPool::SimulationThreadPool(QObject* parent):
    QObject(parent),
    random(new Random(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())),
    running_threads(0)
{
    for (int i = 0; i < QThreadPool::globalInstance()->maxThreadCount(); ++i) {
        setup_thread(random->get_roll());
    }
}

SimulationThreadPool::~SimulationThreadPool() {
    delete random;
    // TODO: Delete threads.
}

void SimulationThreadPool::run_sim(const QString &setup_string) {
    assert(running_threads == 0);
    assert(thread_results.empty());

    for (int i = 0; i < thread_pool.size(); ++i) {
        thread_results.append(QPair<int, double>(thread_pool[i].first, 0.0));
    }

    running_threads = thread_pool.size();
    emit thread_setup_string(setup_string);
}

void SimulationThreadPool::setup_thread(const int thread_id) {
    QThread* thread = new QThread();
    SimulationRunner* runner = new SimulationRunner(QString::number(thread_id));

    connect(this, SIGNAL (thread_setup_string(QString)), runner, SLOT (run_sim(QString)));
    connect(runner, SIGNAL (error(QString, QString)), this, SLOT (error_string(QString, QString)));
    connect(runner, SIGNAL (result(QString, double)), this, SLOT (result(QString, double)));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));

    thread_pool.append(QPair<int, QThread*>(thread_id, thread));

    runner->moveToThread(thread);
    thread->start();
}

void SimulationThreadPool::error_string(QString seed, QString error) {
    qDebug() << "thread error" << seed << ": " << error;
    --running_threads;

    if (running_threads == 0) {
        thread_results.clear();
    }
}

void SimulationThreadPool::result(QString seed, double result) {
    --running_threads;

    for (int i = 0; i < thread_results.size(); ++i) {
        if (thread_results[i].first != seed.toInt())
            continue;

        thread_results[i].second = result;
    }

    check_threads_finished();
}

void SimulationThreadPool::check_threads_finished() {
    if (running_threads == 0) {
        double avg_dps = 0.0;
        int num_threads_with_result = 0;

        for (int i = 0; i < thread_results.size(); ++i) {
            if (thread_results[i].second < 0.001)
                continue;

            ++num_threads_with_result;
            avg_dps += thread_results[i].second;
            if (num_threads_with_result > 1)
                avg_dps /= 2;
        }

        QString avg_dps_string = QString::number(avg_dps, 'f', 2);
        qDebug() << QString("Average dps from %1 threads: %2").arg(QString::number(num_threads_with_result), avg_dps_string);
        thread_result(avg_dps_string);
        thread_results.clear();
    }
}
