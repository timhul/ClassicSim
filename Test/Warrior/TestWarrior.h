#ifndef TESTWARRIOR_H
#define TESTWARRIOR_H

#include "TestCharacter.h"

class EquipmentDb;

class TestWarrior : public TestCharacter {
public:
    void test_all() override;
    void test_basic_properties() override;
};

#endif // TESTWARRIOR_H
