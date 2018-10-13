#ifndef TESTARMS_H
#define TESTARMS_H

#include <QString>

class EquipmentDb;
class Arms;
class Orc;
class Warrior;

class TestArms {
public:
    TestArms(EquipmentDb* equipment_db);

    void test_all();

private:
    EquipmentDb* equipment_db;
    Arms* arms;
    Orc* race;
    Warrior* warrior;

    void set_up();
    void tear_down();

    void test_arms_talents();
    void test_clear_tree();

    QString get_position(const QString& name);

    bool increment_talent_num_times(const QString& name, int num_times);
    bool increment(const QString& name);
    bool decrement(const QString& name);
};

#endif // TESTARMS_H
