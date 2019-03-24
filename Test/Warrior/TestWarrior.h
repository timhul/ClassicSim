#ifndef TESTWARRIOR_H
#define TESTWARRIOR_H

#include "TestObject.h"

class EquipmentDb;

class TestWarrior : public TestObject {
public:
    TestWarrior(EquipmentDb* equipment_db);

    void test_all() override;

private:
    void test_values_after_initialization() override;
};

#endif // TESTWARRIOR_H
