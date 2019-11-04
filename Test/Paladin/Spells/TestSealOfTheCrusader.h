#pragma once

#include "TestSpellPaladin.h"

class TestSealOfTheCrusader: public TestSpellPaladin {
public:
    TestSealOfTheCrusader(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_seal_of_the_crusader_lowers_damage();
    void test_seal_removal_restores_damage();
    void test_resource_cost_1_of_5_benediction();
    void test_resource_cost_2_of_5_benediction();
    void test_resource_cost_3_of_5_benediction();
    void test_resource_cost_4_of_5_benediction();
    void test_resource_cost_5_of_5_benediction();
    void test_melee_ap_bonus_0_of_3_improved_sotc();
    void test_melee_ap_bonus_1_of_3_improved_sotc();
    void test_melee_ap_bonus_2_of_3_improved_sotc();
    void test_melee_ap_bonus_3_of_3_improved_sotc();
    void test_seal_of_the_crusader_removes_active_seal_of_command();
    void test_libram_of_fervor_increases_melee_ap_bonus();
    void test_libram_of_hope_reduces_mana_cost();
    void test_auto_attack_hit_refreshes_duration_while_no_seal_is_active();
    void test_auto_attack_crit_refreshes_duration_while_no_seal_is_active();
    void test_auto_attack_glancing_refreshes_duration_while_no_seal_is_active();
    void test_auto_attack_dodge_does_not_refresh_duration_while_no_seal_is_active();
    void test_auto_attack_miss_does_not_refresh_duration_while_no_seal_is_active();
    void test_auto_attack_hit_refreshes_duration_while_seal_of_command_is_active();
    void test_auto_attack_crit_refreshes_duration_while_seal_of_command_is_active();
    void test_auto_attack_glancing_refreshes_duration_while_seal_of_command_is_active();
    void test_auto_attack_dodge_does_not_refresh_duration_while_seal_of_command_is_active();
    void test_auto_attack_miss_does_not_refresh_duration_while_seal_of_command_is_active();
};
