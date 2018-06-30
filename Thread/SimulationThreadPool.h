#ifndef SIMULATIONTHREADPOOL_H
#define SIMULATIONTHREADPOOL_H

#include <QObject>
#include <QVector>

class Random;
class QThread;

class SimulationThreadPool: public QObject {
    Q_OBJECT
public:
    SimulationThreadPool(QObject* parent = 0);
    ~SimulationThreadPool();

    void run_sim(const QString& setup_string);

public slots:
    void error_string(QString, QString);
    void result(QString, float);

signals:
    void thread_result(QString dps);
    void thread_setup_string(QString setup_string);

protected:
private:
    Random* random;
    int running_threads;

    QVector<QPair<int, float>> thread_results;
    QVector<QPair<int, QThread*>> thread_pool;

    void setup_thread(const int thread_id);
    void check_threads_finished();
};

#endif // SIMULATIONTHREADPOOL_H
