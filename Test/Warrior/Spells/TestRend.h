#ifndef TESTREND_H
#define TESTREND_H

#include "TestSpellWarrior.h"

class Rend;
class Spell;

class TestRend: public TestSpellWarrior {
public:
    TestRend(EquipmentDb *equipment_db);

    void test_all();

    Rend* rend();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_damage_of_0_of_3_improved_rend();
    void test_damage_of_1_of_3_improved_rend();
    void test_damage_of_2_of_3_improved_rend();
    void test_damage_of_3_of_3_improved_rend();

    void given_0_of_3_improved_rend();
    void given_1_of_3_improved_rend();
    void given_2_of_3_improved_rend();
    void given_3_of_3_improved_rend();

    void given_no_previous_rend_damage_dealt();

    void when_rend_is_performed();
    void when_attack_is_performed(Spell* spell);

    void then_rend_damage_dealt_is(const int damage_dealt);
    void then_rend_is_applied();
    void then_rend_is_not_applied();
    void then_damage_is_dealt_over_21_seconds();

private:
};

#endif // TESTREND_H
