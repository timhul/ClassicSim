#pragma once

#include "TestSpellWarlock.h"

class TestShadowBolt : public TestSpellWarlock {
public:
    TestShadowBolt(EquipmentDb* equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg();
    void test_cast_time_1_of_5_bane();
    void test_cast_time_2_of_5_bane();
    void test_cast_time_3_of_5_bane();
    void test_cast_time_4_of_5_bane();
    void test_cast_time_5_of_5_bane();

    void test_resource_cost_1_of_5_cataclysm();
    void test_resource_cost_2_of_5_cataclysm();
    void test_resource_cost_3_of_5_cataclysm();
    void test_resource_cost_4_of_5_cataclysm();
    void test_resource_cost_5_of_5_cataclysm();

    void test_crit_dmg_ruin();

    void test_hit_dmg_demonic_sacrifice();
    void test_crit_dmg_demonic_sacrifice();

    void test_crits_applies_improved_shadow_bolt_debuff_if_talented();
    void test_casting_speed_increases_reduces_casting_time();

    void when_shadow_bolt_is_performed();
};
