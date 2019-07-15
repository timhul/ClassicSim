#pragma once

#include "TestSpellMage.h"

class TestFireball: public TestSpellMage {
public:
    TestFireball(EquipmentDb *equipment_db);

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
    void test_cast_time_1_of_5_improved_fireball();
    void test_cast_time_2_of_5_improved_fireball();
    void test_cast_time_3_of_5_improved_fireball();
    void test_cast_time_4_of_5_improved_fireball();
    void test_cast_time_5_of_5_improved_fireball();

    void test_mana_return_1_of_3_master_of_elements();
    void test_mana_return_2_of_3_master_of_elements();
    void test_mana_return_3_of_3_master_of_elements();

    void test_hit_dmg_1_of_5_fire_power();
    void test_hit_dmg_5_of_5_fire_power();

    void test_1_of_5_ignite();
    void test_5_of_5_ignite();

    void test_hit_dmg_arcane_power();

    void test_casting_speed_increases_reduces_casting_time();

    void when_fireball_is_performed();
};
