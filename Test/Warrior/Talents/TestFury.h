#ifndef TESTFURY_H
#define TESTFURY_H

#include <QString>

class EquipmentDb;
class Fury;
class Orc;
class Warrior;

class TestFury {
public:
    TestFury(EquipmentDb* equipment_db);

    void test_all();

private:
    EquipmentDb* equipment_db;
    Fury* fury;
    Orc* race;
    Warrior* warrior;

    void set_up();
    void tear_down();

    void test_fury_talents();

    QString get_position(const QString& name);

    bool increment_talent_num_times(const QString& name, int num_times);
    bool increment(const QString& name);
    bool decrement(const QString& name);
};

#endif // TESTFURY_H
