#ifndef TESTWARRIOR_H
#define TESTWARRIOR_H

class EquipmentDb;

class TestWarrior {
public:
    TestWarrior();
    ~TestWarrior();

    void test_all();
    void test_char_initialization();

private:
    EquipmentDb* equipment_db;
};

#endif // TESTWARRIOR_H
