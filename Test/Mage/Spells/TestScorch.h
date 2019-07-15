#pragma once

#include "TestSpellMage.h"

class TestScorch: public TestSpellMage {
public:
    TestScorch(EquipmentDb *equipment_db);

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

    void test_mana_return_1_of_3_master_of_elements();
    void test_mana_return_2_of_3_master_of_elements();
    void test_mana_return_3_of_3_master_of_elements();

    void test_hit_dmg_1_of_5_fire_power();
    void test_hit_dmg_5_of_5_fire_power();

    void test_1_of_5_ignite();
    void test_5_of_5_ignite();

    void test_0_of_3_imp_scorch_does_not_apply_debuff_on_hit();
    void test_0_of_3_imp_scorch_does_not_apply_debuff_on_crit();
    void test_3_of_3_imp_scorch_applies_debuff_on_hit();
    void test_3_of_3_imp_scorch_applies_debuff_on_crit();

    void test_hit_dmg_arcane_power();

    void when_scorch_is_performed();
};
