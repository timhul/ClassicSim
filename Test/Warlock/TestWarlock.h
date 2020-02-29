#pragma once

#include "TestObject.h"
#include "TestUtils.h"

class EquipmentDb;

class TestWarlock : public TestObject {
public:
    TestWarlock(EquipmentDb* equipment_db);

    void test_all() override;

private:
    void test_values_after_initialization() override;
};
