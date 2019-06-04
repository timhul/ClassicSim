#ifndef TESTMECHANICS_H
#define TESTMECHANICS_H

#include "TestUtils.h"

class TestMechanics : public TestUtils {
public:
    void test_all();

private:
    void test_glancing_blow_rate();
    void test_glancing_dmg_penalty();
    void test_dw_white_miss();
    void test_2h_white_miss();
    void test_dodge_from_wpn_skill_diff();
    void test_physical_crit_suppression_from_target_level();

    void test_full_resistance_chance();
};

#endif // TESTMECHANICS_H
