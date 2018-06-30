#ifndef TESTOVERPOWER_H
#define TESTOVERPOWER_H

#include "TestSpellWarrior.h"

class TestOverpower: public TestSpellWarrior {
public:
    TestOverpower();

    void test_all();

    Overpower* overpower();

    void test_name_correct();
    void test_has_5_second_cooldown();
    void test_incurs_global_cooldown_on_use();
    void test_costs_5_rage();

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();

    void when_overpower_is_performed();

private:
};

#endif // TESTOVERPOWER_H
