#ifndef TESTROGUE_H
#define TESTROGUE_H

#include "TestCharacter.h"
#include "TestUtils.h"

class EquipmentDb;

class TestRogue : public TestCharacter {
public:
    void test_all() override;

private:
    void test_basic_properties() override;
};

#endif // TESTROGUE_H
