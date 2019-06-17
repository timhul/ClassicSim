#pragma once

#include "TestObject.h"
#include "TestUtils.h"

class EquipmentDb;

class TestMage : public TestObject {
public:
    TestMage(EquipmentDb* equipment_db);

    void test_all() override;

private:
    void test_values_after_initialization() override;
};
