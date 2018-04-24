#ifndef TESTWHIRLWIND_H
#define TESTWHIRLWIND_H

#include "TestSpellWarrior.h"

class TestWhirlwind: public TestSpellWarrior {
public:
    void test_all();

    void test_name_correct();
    void test_has_10_second_cooldown();
    void test_incurs_global_cooldown_on_use();
    void test_costs_25_rage();

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();

    void when_whirlwind_is_performed();

private:
};

#endif // TESTWHIRLWIND_H
