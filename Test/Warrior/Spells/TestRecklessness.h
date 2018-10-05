#ifndef TESTRECKLESSNESS_H
#define TESTRECKLESSNESS_H

#include "TestSpellWarrior.h"

class TestRecklessness: public TestSpellWarrior {
public:
    TestRecklessness(EquipmentDb *equipment_db);

    void test_all();

    Recklessness* recklessness();

    void test_name_correct();
    void test_has_1800_second_cooldown();
    void test_crit_reduced_after_buff_expires();
    void test_incurs_global_cooldown_on_use();
    void test_costs_0_rage();
    void test_ability_miss_still_misses();
    void test_ability_dodge_still_dodges();
    void test_ability_parry_still_parries();
    void test_ability_block_still_blocks();
    void test_white_miss_still_misses();
    void test_white_dodge_still_dodges();
    void test_white_parry_still_parries();
    void test_white_block_still_blocks();
    void test_glancing_hits_converted_to_crits();
    void test_white_hit_converted_to_crit();
    void test_white_crit_still_crits();
    void test_ability_hit_converted_to_crit();
    void test_ability_crit_still_crits();

    void when_recklessness_is_performed();
    void when_reck_and_mh_attack_is_performed();
    void when_reck_and_whirlwind_is_performed();

private:
};

#endif // TESTRECKLESSNESS_H
