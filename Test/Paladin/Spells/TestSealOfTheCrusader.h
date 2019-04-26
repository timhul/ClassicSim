#ifndef TESTSEALOFTHECRUSADER_H
#define TESTSEALOFTHECRUSADER_H

#include "TestSpellPaladin.h"

class MainhandAttackPaladin;
class SealOfTheCrusader;

class TestSealOfTheCrusader: public TestSpellPaladin {
public:
    TestSealOfTheCrusader(EquipmentDb *equipment_db);

    void test_all();

private:
    MainhandAttackPaladin* mh_attack();
    SealOfTheCrusader* seal_of_the_crusader();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
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

    void given_seal_of_the_crusader_is_active();
    void when_mh_attack_is_performed();
    void when_seal_of_the_crusader_is_performed();
    void then_next_expected_use_is(const double next_expected_use);

    void given_benediction_rank(const unsigned num);
    void given_improved_sotc_rank(const unsigned num);
};

#endif // TESTSEALOFTHECRUSADER_H
