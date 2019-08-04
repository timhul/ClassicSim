#pragma once

#include "TestSpellDruid.h"

class TestFerociousBite: public TestSpellDruid {
public:
    TestFerociousBite(EquipmentDb *equipment_db);

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
    void test_ferocious_bite_spends_combo_points();
    void test_hit_dmg_feral_aggression_5_of_5();
    void test_crit_dmg_feral_aggression_5_of_5();

    void given_druid_in_cat_form();
    void when_ferocious_bite_is_performed();
    void when_shred_is_performed();
};
