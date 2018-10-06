#ifndef TESTBERSERKERSTANCE_H
#define TESTBERSERKERSTANCE_H

#include "TestSpellWarrior.h"

class TestBerserkerStance: public TestSpellWarrior {
public:
    TestBerserkerStance(EquipmentDb* equipment_db);

    void test_all();

    BerserkerStance* berserker_stance();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_does_not_incur_extra_global_cooldown_if_gcd_longer_than_half_second();
    void test_gives_crit_when_stance_entered();
    void test_removes_crit_when_stance_exited();
    void test_0_rage_remains_after_stance_switch_with_0_of_5_tactical_mastery();
    void test_5_rage_remains_after_stance_switch_with_1_of_5_tactical_mastery();
    void test_10_rage_remains_after_stance_switch_with_2_of_5_tactical_mastery();
    void test_15_rage_remains_after_stance_switch_with_3_of_5_tactical_mastery();
    void test_20_rage_remains_after_stance_switch_with_4_of_5_tactical_mastery();
    void test_25_rage_remains_after_stance_switch_with_5_of_5_tactical_mastery();
    void test_rage_is_not_increased_by_switching_stances_with_5_of_5_tactical_mastery();

    void when_berserker_stance_is_performed();

private:
};

#endif // TESTBERSERKERSTANCE_H
