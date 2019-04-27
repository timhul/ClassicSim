#ifndef TESTJUDGEMENT_H
#define TESTJUDGEMENT_H

#include "TestSpellPaladin.h"

class MainhandAttackPaladin;
class Judgement;

class TestJudgement: public TestSpellPaladin {
public:
    TestJudgement(EquipmentDb *equipment_db);

    void test_all();

private:
    MainhandAttackPaladin* mh_attack();
    SealOfTheCrusader* seal_of_the_crusader();
    Judgement* judgement();

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

    void test_auto_hit_refreshes_judgement_of_the_crusader();
    void test_judgement_of_the_crusader_deals_zero_damage();
    void test_judgement_of_the_crusader_holy_dmg_bonus_0_of_3_improved_sotc();
    void test_judgement_of_the_crusader_holy_dmg_bonus_1_of_3_improved_sotc();
    void test_judgement_of_the_crusader_holy_dmg_bonus_2_of_3_improved_sotc();
    void test_judgement_of_the_crusader_holy_dmg_bonus_3_of_3_improved_sotc();

    void given_seal_of_the_crusader_is_active();
    void when_mh_attack_is_performed();
    void when_judgement_is_performed();
    void when_seal_of_the_crusader_is_performed();
    void then_next_expected_use_is(const double next_expected_use);

    void given_benediction_rank(const unsigned num);
    void given_improved_sotc_rank(const unsigned num);
};

#endif // TESTJUDGEMENT_H
