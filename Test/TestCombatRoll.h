#pragma once

#include "TestUtils.h"

class EquipmentDb;

class TestCombatRoll : public TestUtils {
public:
    TestCombatRoll(EquipmentDb* equipment_db);

    void test_all();

private:
    EquipmentDb* equipment_db;

    void test_glancing_penalties();
};
