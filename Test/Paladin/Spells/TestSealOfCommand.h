#ifndef TESTSEALOFCOMMAND_H
#define TESTSEALOFCOMMAND_H

#include "TestSpellPaladin.h"

class TestSealOfCommand: public TestSpellPaladin {
public:
    TestSealOfCommand(EquipmentDb *equipment_db);

    void test_all();

private:
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
};

#endif // TESTSEALOFCOMMAND_H
