#ifndef TESTRECKLESSNESS_H
#define TESTRECKLESSNESS_H

#include "TestSpellWarrior.h"

class TestRecklessness: public TestSpellWarrior {
public:
    TestRecklessness(EquipmentDb *equipment_db);

    void test_all();

private:
    Recklessness* recklessness();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_crit_reduced_after_buff_expires();
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
};

#endif // TESTRECKLESSNESS_H
