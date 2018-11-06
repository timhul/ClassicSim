#ifndef SIMULATIONRUNNER_H
#define SIMULATIONRUNNER_H

#include <QObject>
#include <QMap>

#include "EnchantName.h"

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
    ~SimulationRunner();

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
    Rotation* rotation;
    SimSettings* global_sim_settings;
    SimSettings* local_sim_settings;
    NumberCruncher* scaler;
    bool full_sim;
    unsigned thread_id;

    QString setup_string;

    QMap<QString, Character*> chars;
    QMap<QString, Race*> races;

    void setup_race(CharacterDecoder& decoder);
    void setup_pchar(CharacterDecoder& decoder);
    void equip_gear(CharacterDecoder& decoder);
    void invest_talent_points(CharacterDecoder& decoder);
    void add_points_to_talent_tree(CharacterDecoder &decoder, const QString& tree_position);
    void apply_external_buffs(CharacterDecoder& decoder);
    void apply_enchants(CharacterDecoder& decoder);
    void apply_ruleset(CharacterDecoder& decoder);
    void setup_target(CharacterDecoder& decoder);
    void select_rotation(CharacterDecoder& decoder);
    void exit_thread(QString err);

    EnchantName::Name get_enum_val(QString enum_val_as_string);
};

#endif // SIMULATIONRUNNER_H
