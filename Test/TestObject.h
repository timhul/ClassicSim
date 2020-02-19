#pragma once

#include <cassert>

#include <QDebug>

#include "TestUtils.h"

class EquipmentDb;

class TestObject : public TestUtils {
public:
    TestObject(EquipmentDb* equipment_db);
    virtual ~TestObject() = default;

    virtual void test_all() = 0;

protected:
    EquipmentDb* equipment_db;

    virtual void test_values_after_initialization() = 0;
};
