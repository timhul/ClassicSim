#ifndef TESTSEALOFTHECRUSADER_H
#define TESTSEALOFTHECRUSADER_H

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
};

#endif // TESTSEALOFTHECRUSADER_H
