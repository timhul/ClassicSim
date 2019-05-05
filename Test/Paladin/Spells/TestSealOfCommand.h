#ifndef TESTSEALOFCOMMAND_H
#define TESTSEALOFCOMMAND_H

#include "TestSpellPaladin.h"

class Proc;

class TestSealOfCommand: public TestSpellPaladin {
public:
    TestSealOfCommand(EquipmentDb *equipment_db);

    void test_all();

private:
    Proc* seal_of_command_proc();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_resource_cost_1_of_5_benediction();
    void test_resource_cost_2_of_5_benediction();
    void test_resource_cost_3_of_5_benediction();
    void test_resource_cost_4_of_5_benediction();
    void test_resource_cost_5_of_5_benediction();
    void test_seal_of_command_removes_active_seal_of_the_crusader();
    void test_libram_of_hope_reduces_mana_cost();
    void test_proc_rate_with_given_weapon_speed();
};

#endif // TESTSEALOFCOMMAND_H
