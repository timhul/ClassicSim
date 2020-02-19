#pragma once

#include "TestSpellDruid.h"

class TestShred : public TestSpellDruid {
public:
    TestShred(EquipmentDb* equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;
    void test_resource_cost_1_of_2_improved_shred();
    void test_resource_cost_2_of_2_improved_shred();
    void test_hit_dmg();
    void test_crit_dmg();
    void test_shred_hit_with_0_of_2_blood_frenzy_awards_1_combo_point();
    void test_shred_crit_with_0_of_2_blood_frenzy_awards_1_combo_point();
    void test_shred_hit_with_2_of_2_blood_frenzy_awards_1_combo_point();
    void test_shred_crit_with_2_of_2_blood_frenzy_awards_2_combo_points();

    void given_druid_in_cat_form();
    void when_shred_is_performed();
};
