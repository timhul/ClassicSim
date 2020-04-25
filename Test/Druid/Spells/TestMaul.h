#pragma once

#include "TestSpellDruid.h"

class TestMaul : public TestSpellDruid {
public:
    TestMaul(EquipmentDb* equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;
    void test_resource_cost_1_of_5_ferocity();
    void test_resource_cost_2_of_5_ferocity();
    void test_resource_cost_3_of_5_ferocity();
    void test_resource_cost_4_of_5_ferocity();
    void test_resource_cost_5_of_5_ferocity();
    void test_hit_dmg_1_of_2_savage_fury();
    void test_hit_dmg_2_of_2_savage_fury();
    void test_hit_dmg();
    void test_hit_threat();
    void test_crit_dmg();

    void given_druid_in_bear_form();
    void when_maul_is_performed();
};
