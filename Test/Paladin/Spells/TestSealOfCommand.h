#ifndef TESTSEALOFCOMMAND_H
#define TESTSEALOFCOMMAND_H

#include "TestSpellPaladin.h"

class MainhandAttackPaladin;
class SealOfTheCrusader;

class TestSealOfCommand: public TestSpellPaladin {
public:
    TestSealOfCommand(EquipmentDb *equipment_db);

    void test_all();

private:
    MainhandAttackPaladin* mh_attack();
    SealOfCommand* seal_of_command();

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

    void given_seal_of_command_is_active();
    void when_mh_attack_is_performed();
    void when_seal_of_command_is_performed();
    void then_next_expected_use_is(const double next_expected_use);

    void given_benediction_rank(const unsigned num);
    void given_seal_of_command_is_enabled();
};

#endif // TESTSEALOFCOMMAND_H
