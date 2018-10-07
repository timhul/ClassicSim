#ifndef TESTCHARACTER_H
#define TESTCHARACTER_H

#include "TestUtils.h"

class EquipmentDb;

class TestCharacter : public TestUtils {
public:
    TestCharacter();
    virtual ~TestCharacter();

    virtual void test_all() = 0;

protected:
    EquipmentDb* equipment_db;

    virtual void test_basic_properties() = 0;
};

#endif // TESTCHARACTER_H
