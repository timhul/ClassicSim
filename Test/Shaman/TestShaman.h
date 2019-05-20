#pragma once

#include "TestObject.h"
#include "TestUtils.h"

class EquipmentDb;

class TestShaman : public TestObject {
public:
    TestShaman(EquipmentDb* equipment_db);

    void test_all() override;

private:
    void test_values_after_initialization() override;
};
