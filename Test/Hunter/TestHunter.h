#ifndef TESTHUNTER_H
#define TESTHUNTER_H

#include "TestCharacter.h"
#include "TestUtils.h"

class EquipmentDb;

class TestHunter : public TestCharacter {
public:
    void test_all() override;

private:
    void test_basic_properties() override;
};

#endif // TESTHUNTER_H
