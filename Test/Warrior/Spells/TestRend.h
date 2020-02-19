#pragma once

#include "TestSpellWarrior.h"

class Rend;
class Spell;

class TestRend : public TestSpellWarrior {
public:
    TestRend(EquipmentDb* equipment_db);

    void test_all();

private:
    Rend* rend() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_damage_of_0_of_3_improved_rend();
    void test_damage_of_1_of_3_improved_rend();
    void test_damage_of_2_of_3_improved_rend();
    void test_damage_of_3_of_3_improved_rend();
    void test_dodge_applies_overpower_buff();

    void given_0_of_3_improved_rend();
    void given_1_of_3_improved_rend();
    void given_2_of_3_improved_rend();
    void given_3_of_3_improved_rend();

    void given_no_previous_rend_damage_dealt();

    void when_rend_is_performed();
    void when_attack_is_performed(Spell* spell);

    void then_rend_damage_dealt_is(const int damage_dealt);
    void then_damage_is_dealt_over_21_seconds();
};
