#pragma once

#include "TestObject.h"

class Target;

class TestTarget : public TestObject {
public:
    TestTarget();
    void test_all() override;

private:
    Target* target {nullptr};

    void set_up();
    void tear_down();

    void test_values_after_initialization() override;
    void test_armor_increase_does_increase_armor();
    void test_armor_decrease_does_decrease_armor();
    void test_armor_never_reduced_below_zero();
    void test_armor_increase_does_not_increase_armor_if_other_effects_outweigh();
};
