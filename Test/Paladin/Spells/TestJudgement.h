#pragma once

#include "TestSpellPaladin.h"

class Judgement;

class TestJudgement : public TestSpellPaladin {
public:
    TestJudgement(EquipmentDb* equipment_db);

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

    void test_cooldown_1_of_2_improved_judgement();
    void test_cooldown_2_of_2_improved_judgement();

    void test_auto_hit_refreshes_judgement_of_the_crusader();
    void test_judgement_of_the_crusader_deals_zero_damage();
    void test_judgement_of_the_crusader_holy_dmg_bonus_0_of_3_improved_sotc();
    void test_judgement_of_the_crusader_holy_dmg_bonus_1_of_3_improved_sotc();
    void test_judgement_of_the_crusader_holy_dmg_bonus_2_of_3_improved_sotc();
    void test_judgement_of_the_crusader_holy_dmg_bonus_3_of_3_improved_sotc();
    void test_judgement_of_the_crusader_r10_pvp_glove_bonus_increases_holy_damage_bonus();
    void test_judgement_of_the_crusader_r13_pvp_glove_bonus_increases_holy_damage_bonus();

    void test_judgement_of_command_damage();
    void test_judgement_of_command_damage_with_sotc_and_sanctity_aura_and_vengeance();

    void given_sanctity_aura_is_active();
    void given_vengeance_is_active(const unsigned num);

    void when_judgement_is_performed();
};
