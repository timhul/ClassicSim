#pragma once

#include "TestObject.h"

class EquipmentDb;

class TestRogue : public TestObject {
public:
    TestRogue(EquipmentDb* equipment_db);

    void test_all() override;

private:
    void test_values_after_initialization() override;
};
