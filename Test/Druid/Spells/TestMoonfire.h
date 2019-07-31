#pragma once

#include "TestSpellDruid.h"

class TestMoonfire: public TestSpellDruid {
public:
    TestMoonfire(EquipmentDb *equipment_db);

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
    void test_crit_dmg_5_of_5_vengeance_and_5_of_imp_moonfire();
    void test_duration_dmg_after_hit();
    void test_duration_dmg_after_crit();
    void test_hit_damage_1_of_5_moonfury();
    void test_hit_damage_5_of_5_moonfury();
    void test_resource_cost_3_of_3_moonglow();

    void when_moonfire_is_performed();
};
