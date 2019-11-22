#pragma once

#include "TestObject.h"

class Stats;

class TestStats : TestObject {
public:
    TestStats();

    void test_all() override;

private:
    Stats* stats {nullptr};

    void set_up();
    void tear_down();

    void test_values_after_initialization() override;
    void test_values_after_add_and_remove_from_another_stats_element();
    void test_weapon_skill_gains();
};
