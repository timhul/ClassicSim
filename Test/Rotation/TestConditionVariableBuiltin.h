#ifndef TESTCONDITIONVARIABLEBUILTIN_H
#define TESTCONDITIONVARIABLEBUILTIN_H

#include "TestCharacter.h"

class ConditionVariableBuiltin;
class Rogue;

class TestConditionVariableBuiltin : TestCharacter {
public:
    void test_all() override;

private:
    void test_basic_properties() override;
    void test_combo_points_less();
    void test_combo_points_leq();
    void test_combo_points_equal();
    void test_combo_points_geq();
    void test_combo_points_greater();
};

#endif // TESTCONDITIONVARIABLEBUILTIN_H
