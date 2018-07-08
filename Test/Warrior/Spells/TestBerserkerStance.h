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

    void given_warrior_in_battle_stance();
    void when_berserker_stance_is_performed();
    void when_whirlwind_is_performed();

private:
};

#endif // TESTBERSERKERSTANCE_H
