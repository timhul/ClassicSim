
#include "SimulationThreadPool.h"
#include "SimulationRunner.h"
#include "Random.h"
#include <limits.h>
#include <QThread>
#include <QDebug>

SimulationThreadPool::SimulationThreadPool(QObject* parent):
    QObject(parent),
    random(new Random(std::numeric_limits<int>::min(), std::numeric_limits<int>::max())),
    running_threads(0)
{}

SimulationThreadPool::~SimulationThreadPool() {
    delete random;
}

void SimulationThreadPool::run_sim(const QString &setup_string) {
    const int num_threads = 4;
    running_threads += num_threads;

    for (int i = 0; i < num_threads; ++i) {
        int seed = random->get_roll();
        thread_results.append(QPair<int, float>(seed, 0.0));
        setup_thread(setup_string, QString::number(seed));
    }
}

void SimulationThreadPool::setup_thread(const QString &setup_string, const QString &thread_id) {
    QThread* thread = new QThread();
    SimulationRunner* runner = new SimulationRunner(setup_string, thread_id);

    runner->moveToThread(thread);

    connect(runner, SIGNAL (error(QString, QString)), this, SLOT (error_string(QString, QString)));
    connect(runner, SIGNAL (result(QString, QString)), this, SLOT (result(QString, QString)));
    connect(thread, SIGNAL (started()), runner, SLOT (run_sim()));
    connect(runner, SIGNAL (finished()), thread, SLOT (quit()));
    connect(runner, SIGNAL (finished()), runner, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));

    thread->start();
}

void SimulationThreadPool::error_string(QString seed, QString error) {
    qDebug() << "thread error" << seed << ": " << error;
    --running_threads;
}

void SimulationThreadPool::result(QString seed, QString result) {
    --running_threads;

    int seed_int = seed.toInt();

    for (int i = 0; i < thread_results.size(); ++i) {
        if (thread_results[i].first != seed_int)
            continue;

        thread_results[i].second = result.toFloat();
    }

    if (running_threads == 0) {
        float avg_dps = 0.0;
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
