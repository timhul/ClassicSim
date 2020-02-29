#pragma once

#include "TestSpellWarlock.h"

class TestLifeTap : public TestSpellWarlock {
public:
    TestLifeTap(EquipmentDb* equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_life_tap_scaling_with_spell_power();
    void test_1_of_2_improved_life_tap();
    void test_2_of_2_improved_life_tap();

    void when_life_tap_is_performed();
};
