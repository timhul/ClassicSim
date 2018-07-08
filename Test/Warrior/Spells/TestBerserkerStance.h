#ifndef TESTBERSERKERSTANCE_H
#define TESTBERSERKERSTANCE_H

#include "TestSpellWarrior.h"

class TestBerserkerStance: public TestSpellWarrior {
public:
    TestBerserkerStance();

    void test_all();

    BerserkerStance* berserker_stance();

    void test_name_correct();
    void test_has_no_cooldown();
    void test_incurs_1_second_stance_cooldown_on_use();
    void test_incurs_half_second_global_cooldown_if_not_on_gcd();
    void test_does_not_incur_extra_global_cooldown_if_gcd_longer_than_half_second();
    void test_costs_0_rage();
    void test_gives_crit_when_stance_entered();
    void test_removes_crit_when_stance_exited();
    void test_0_rage_remains_after_stance_switch_with_0_of_5_tactical_mastery();
    void test_5_rage_remains_after_stance_switch_with_1_of_5_tactical_mastery();
    void test_10_rage_remains_after_stance_switch_with_2_of_5_tactical_mastery();
    void test_15_rage_remains_after_stance_switch_with_3_of_5_tactical_mastery();
    void test_20_rage_remains_after_stance_switch_with_4_of_5_tactical_mastery();
    void test_25_rage_remains_after_stance_switch_with_5_of_5_tactical_mastery();
    void test_rage_is_not_increased_by_switching_stances_with_5_of_5_tactical_mastery();

    void given_warrior_in_battle_stance();
    void when_berserker_stance_is_performed();
    void when_whirlwind_is_performed();

private:
};

#endif // TESTBERSERKERSTANCE_H
