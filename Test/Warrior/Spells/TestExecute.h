#ifndef TESTEXECUTE_H
#define TESTEXECUTE_H

#include "TestSpellWarrior.h"

class Execute;

class TestExecute: public TestSpellWarrior {
public:
    TestExecute(EquipmentDb *equipment_db);

    void test_all();

private:
    Execute* execute();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

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

    void test_dodge_applies_overpower_buff();

    void given_0_of_2_improved_execute();
    void given_1_of_2_improved_execute();
    void given_2_of_2_improved_execute();
    void given_target_in_execute_range();
    void given_target_not_in_execute_range();

    void when_execute_is_performed_with_rage(const unsigned rage);
    bool execute_available_with_rage(const unsigned rage);
};

#endif // TESTEXECUTE_H
