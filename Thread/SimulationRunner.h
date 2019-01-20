#ifndef SIMULATIONRUNNER_H
#define SIMULATIONRUNNER_H

#include <QObject>
#include <QMap>

class Character;
class CharacterDecoder;
class CombatRoll;
class Engine;
class Equipment;
class EquipmentDb;
class Faction;
class Race;
class Rotation;
class SimSettings;
class NumberCruncher;
class Target;

class SimulationRunner: public QObject {
    Q_OBJECT
public:
    SimulationRunner(unsigned thread_id,
                     EquipmentDb* equipment_db,
                     SimSettings* sim_settings,
                     NumberCruncher* scaler,
                     QObject* parent = nullptr);
    ~SimulationRunner() = default;

public slots:
    void run_sim(unsigned thread_id, QString setup_string, bool full_sim, int iterations);

signals:
    void finished();
    void result();
    void error(QString seed, QString err);

protected:
private:
    Character* pchar;
    EquipmentDb* equipment_db;
    Race* race;
    SimSettings* global_sim_settings;
    SimSettings* local_sim_settings;
    NumberCruncher* scaler;
    bool full_sim;
    unsigned thread_id;

    QString setup_string;

    QMap<QString, Character*> chars;
    QMap<QString, Race*> races;

    void exit_thread(QString err);
};

#endif // SIMULATIONRUNNER_H
