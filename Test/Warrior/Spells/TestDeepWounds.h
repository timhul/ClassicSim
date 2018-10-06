#ifndef TESTDEEPWOUNDS_H
#define TESTDEEPWOUNDS_H

#include "TestSpellWarrior.h"

class Spell;

class TestDeepWounds: public TestSpellWarrior {
public:
    TestDeepWounds(EquipmentDb *equipment_db);

    void test_all();

    DeepWounds* deep_wounds();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_critical_mh_attack_applies_deep_wounds();
    void test_critical_oh_attack_applies_deep_wounds();
    void test_critical_bloodthirst_applies_deep_wounds();
    void test_critical_whirlwind_applies_deep_wounds();
    void test_critical_heroic_strike_applies_deep_wounds();
    void test_critical_overpower_applies_deep_wounds();

    void test_regular_hit_mh_attack_does_not_apply_deep_wounds();
    void test_regular_hit_oh_attack_does_not_apply_deep_wounds();
    void test_regular_hit_bloodthirst_does_not_apply_deep_wounds();
    void test_regular_hit_whirlwind_does_not_apply_deep_wounds();
    void test_regular_hit_heroic_strike_does_not_apply_deep_wounds();
    void test_regular_hit_overpower_does_not_apply_deep_wounds();

    void test_damage_of_1_of_3_deep_wounds();
    void test_damage_of_2_of_3_deep_wounds();
    void test_damage_of_3_of_3_deep_wounds();

    void test_damage_stacks_when_multiple_crits_occur();

    void given_deep_wounds_enabled();

    void given_0_of_3_deep_wounds();
    void given_1_of_3_deep_wounds();
    void given_2_of_3_deep_wounds();
    void given_3_of_3_deep_wounds();

    void given_no_previous_deep_wounds_damage_dealt();

    void when_mh_attack_is_performed();
    void when_attack_is_performed(Spell* spell);

    void then_deep_wounds_damage_dealt_is(const int damage_dealt);
    void then_deep_wounds_is_applied();
    void then_deep_wounds_is_not_applied();
    void then_damage_is_dealt_over_12_seconds();

private:
};

#endif // TESTDEEPWOUNDS_H
