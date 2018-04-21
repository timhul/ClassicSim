#ifndef TESTEXECUTE_H
#define TESTEXECUTE_H

#include "TestSpellWarrior.h"

class TestExecute: public TestSpellWarrior {
public:
    void test_all();

    void test_name_correct();
    void test_has_no_cooldown();
    void test_incurs_global_cooldown_on_use();
    void test_1_of_2_improved_execute_reduces_rage_cost();
    void test_2_of_2_improved_execute_reduces_rage_cost();
    void test_removing_points_in_improved_execute_increases_rage_cost();

    void test_min_crit_dmg_0_of_2_imp_execute_0_of_2_impale();
    void test_max_crit_dmg_0_of_2_imp_execute_0_of_2_impale();

    void test_min_crit_dmg_1_of_2_imp_execute_0_of_2_impale();
    void test_max_crit_dmg_1_of_2_imp_execute_0_of_2_impale();

    void test_min_crit_dmg_2_of_2_imp_execute_0_of_2_impale();
    void test_max_crit_dmg_2_of_2_imp_execute_0_of_2_impale();

    void test_min_crit_dmg_0_of_2_imp_execute_1_of_2_impale();
    void test_max_crit_dmg_0_of_2_imp_execute_1_of_2_impale();

    void test_min_crit_dmg_1_of_2_imp_execute_1_of_2_impale();
    void test_max_crit_dmg_1_of_2_imp_execute_1_of_2_impale();

    void test_min_crit_dmg_2_of_2_imp_execute_1_of_2_impale();
    void test_max_crit_dmg_2_of_2_imp_execute_1_of_2_impale();

    void test_min_crit_dmg_0_of_2_imp_execute_2_of_2_impale();
    void test_max_crit_dmg_0_of_2_imp_execute_2_of_2_impale();

    void test_min_crit_dmg_1_of_2_imp_execute_2_of_2_impale();
    void test_max_crit_dmg_1_of_2_imp_execute_2_of_2_impale();

    void test_min_crit_dmg_2_of_2_imp_execute_2_of_2_impale();
    void test_max_crit_dmg_2_of_2_imp_execute_2_of_2_impale();

    void given_0_of_2_improved_execute();
    void given_1_of_2_improved_execute();
    void given_2_of_2_improved_execute();

    void when_execute_is_performed_with_rage(const int rage);

private:
};

#endif // TESTEXECUTE_H
