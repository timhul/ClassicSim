#ifndef TESTCONDITIONVARIABLEBUILTIN_H
#define TESTCONDITIONVARIABLEBUILTIN_H

#include "TestObject.h"

class ConditionVariableBuiltin;
class Rogue;

class TestConditionVariableBuiltin : TestObject {
public:
    TestConditionVariableBuiltin();
    void test_all() override;

private:
    void test_values_after_initialization() override;
    void test_combo_points_less();
    void test_combo_points_leq();
    void test_combo_points_equal();
    void test_combo_points_geq();
    void test_combo_points_greater();
};

#endif // TESTCONDITIONVARIABLEBUILTIN_H
