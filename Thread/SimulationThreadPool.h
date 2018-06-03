#ifndef SIMULATIONTHREADPOOL_H
#define SIMULATIONTHREADPOOL_H

#include <QObject>
#include <QVector>

class Random;

class SimulationThreadPool: public QObject {
    Q_OBJECT
public:
    SimulationThreadPool(QObject* parent = 0);
    ~SimulationThreadPool();

    void run_sim(const QString& setup_string);

public slots:
    void error_string(QString, QString);
    void result(QString, QString);

signals:
    void thread_result(QString dps);

protected:
private:
    Random* random;
    int running_threads;

    QVector<QPair<int, float>> thread_results;

    void setup_thread(const QString& setup_string, const QString& thread_id);
};

#endif // SIMULATIONTHREADPOOL_H
