#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H

#include "TestUtils.h"

#include <QDebug>

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

#endif // TESTCHARACTER_H
