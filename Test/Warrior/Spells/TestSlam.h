#ifndef TESTSLAM_H
#define TESTSLAM_H

#include "TestSpellWarrior.h"

class TestSlam: public TestSpellWarrior {
public:
    TestSlam(EquipmentDb *equipment_db);

    void test_all();

private:
    Slam* slam();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();
    void test_dodge_applies_overpower_buff();

    void test_cast_time_with_0_of_5_improved_slam();
    void test_cast_time_with_1_of_5_improved_slam();
    void test_cast_time_with_2_of_5_improved_slam();
    void test_cast_time_with_3_of_5_improved_slam();
    void test_cast_time_with_4_of_5_improved_slam();
    void test_cast_time_with_5_of_5_improved_slam();

    void test_auto_attacks_cancelled_during_slam_cast();

    void when_slam_is_performed();

    void given_1_of_5_improved_slam();
    void given_2_of_5_improved_slam();
    void given_3_of_5_improved_slam();
    void given_4_of_5_improved_slam();
    void given_5_of_5_improved_slam();
};

#endif // TESTSLAM_H
