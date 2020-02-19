#pragma once

#include "TestSpellMage.h"

class TestFrostbolt : public TestSpellMage {
public:
    TestFrostbolt(EquipmentDb* equipment_db);

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
    void test_cast_time_1_of_5_improved_frostbolt();
    void test_cast_time_2_of_5_improved_frostbolt();
    void test_cast_time_3_of_5_improved_frostbolt();
    void test_cast_time_4_of_5_improved_frostbolt();
    void test_cast_time_5_of_5_improved_frostbolt();

    void test_mana_return_1_of_3_master_of_elements();
    void test_mana_return_2_of_3_master_of_elements();
    void test_mana_return_3_of_3_master_of_elements();

    void test_hit_dmg_1_of_3_piercing_ice();
    void test_hit_dmg_3_of_3_piercing_ice();

    void test_crit_dmg_1_of_5_ice_shards();
    void test_crit_dmg_5_of_5_ice_shards();

    void test_crits_do_not_apply_ignite();
    void test_casting_speed_increases_reduces_casting_time();

    void test_hit_dmg_arcane_power();

    void when_frostbolt_is_performed();
};
