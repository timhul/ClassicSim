#pragma once

#include "TestSpellDruid.h"

class TestStarfire: public TestSpellDruid {
public:
    TestStarfire(EquipmentDb *equipment_db);

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
    void test_hit_damage_1_of_5_moonfury();
    void test_hit_damage_5_of_5_moonfury();
    void test_cast_time_1_of_5_improved_starfire();
    void test_cast_time_2_of_5_improved_starfire();
    void test_cast_time_3_of_5_improved_starfire();
    void test_cast_time_4_of_5_improved_starfire();
    void test_cast_time_5_of_5_improved_starfire();

    void test_casting_speed_increases_reduces_casting_time();

    void when_starfire_is_performed();
};
