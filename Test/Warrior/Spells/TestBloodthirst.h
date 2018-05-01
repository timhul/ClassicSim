#ifndef TESTBLOODTHIRST_H
#define TESTBLOODTHIRST_H

#include "TestSpellWarrior.h"

class TestBloodthirst: public TestSpellWarrior {
public:
    void test_all();

    Bloodthirst* bloodthirst();

    void test_name_correct();
    void test_has_6_second_cooldown();
    void test_incurs_global_cooldown_on_use();
    void test_costs_30_rage();

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();

    void when_bloodthirst_is_performed();

private:
};

#endif // TESTBLOODTHIRST_H
