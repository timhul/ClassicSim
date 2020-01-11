#pragma once

#include "TestSpellRogue.h"

class Eviscerate;

class TestEviscerate: public TestSpellRogue {
public:
    TestEviscerate(EquipmentDb *equipment_db);

    void test_all();

private:
    Eviscerate* eviscerate() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;
    void test_combo_points() override;
    void test_stealth() override;

    void test_hit_dmg_1_combo_points();
    void test_hit_dmg_2_combo_points();
    void test_hit_dmg_3_combo_points();
    void test_hit_dmg_4_combo_points();
    void test_hit_dmg_5_combo_points();

    void test_crit_dmg_1_combo_points();
    void test_crit_dmg_2_combo_points();
    void test_crit_dmg_3_combo_points();
    void test_crit_dmg_4_combo_points();
    void test_crit_dmg_5_combo_points();

    void test_hit_dmg_5_combo_points_with_1_of_3_imp_evisc();
    void test_hit_dmg_5_combo_points_with_2_of_3_imp_evisc();
    void test_hit_dmg_5_combo_points_with_3_of_3_imp_evisc();

    void test_crit_dmg_5_combo_points_with_1_of_3_imp_evisc();
    void test_crit_dmg_5_combo_points_with_2_of_3_imp_evisc();
    void test_crit_dmg_5_combo_points_with_3_of_3_imp_evisc();

    void test_hit_dmg_5_combo_points_with_1_of_3_aggression();
    void test_hit_dmg_5_combo_points_with_2_of_3_aggression();
    void test_hit_dmg_5_combo_points_with_3_of_3_aggression();

    void test_crit_dmg_5_combo_points_with_1_of_3_aggression();
    void test_crit_dmg_5_combo_points_with_2_of_3_aggression();
    void test_crit_dmg_5_combo_points_with_3_of_3_aggression();

    void test_hit_dmg_5_combo_points_with_3_of_3_imp_evisc_and_3_of_3_aggression_and_5_pc_deathdealer();
    void test_crit_dmg_5_combo_points_with_3_of_3_imp_evisc_and_3_of_3_aggression_and_5_pc_deathdealer();

    void given_5_pc_deathdealer();

    void when_eviscerate_is_performed();
};
