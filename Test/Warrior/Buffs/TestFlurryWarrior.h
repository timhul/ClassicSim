#ifndef TESTFLURRYWARRIOR_H
#define TESTFLURRYWARRIOR_H

#include "TestBuffWarrior.h"

class Buff;
class Spell;

class TestFlurryWarrior: public TestBuffWarrior {
public:
    TestFlurryWarrior(EquipmentDb *equipment_db);

    void test_all();

private:
    void test_name_correct();
    void test_has_15_second_duration();
    void test_has_3_charges();
    void test_attack_speed_increased_when_1_of_5_flurry_applied();
    void test_attack_speed_increased_when_2_of_5_flurry_applied();
    void test_attack_speed_increased_when_3_of_5_flurry_applied();
    void test_attack_speed_increased_when_4_of_5_flurry_applied();
    void test_attack_speed_increased_when_5_of_5_flurry_applied();

    void test_attack_speed_decreased_when_1_of_5_flurry_removed();
    void test_attack_speed_decreased_when_2_of_5_flurry_removed();
    void test_attack_speed_decreased_when_3_of_5_flurry_removed();
    void test_attack_speed_decreased_when_4_of_5_flurry_removed();
    void test_attack_speed_decreased_when_5_of_5_flurry_removed();

    void test_critical_mh_attack_applies_flurry();
    void test_critical_oh_attack_applies_flurry();
    void test_critical_bloodthirst_applies_flurry();
    void test_critical_whirlwind_applies_flurry();
    void test_critical_heroic_strike_applies_flurry();
    void test_critical_overpower_applies_flurry();
    void test_critical_mortal_strike_applies_flurry();

    void test_regular_hit_mh_attack_does_not_apply_flurry();
    void test_regular_hit_oh_attack_does_not_apply_flurry();
    void test_regular_hit_bloodthirst_does_not_apply_flurry();
    void test_regular_hit_whirlwind_does_not_apply_flurry();
    void test_regular_hit_heroic_strike_does_not_apply_flurry();
    void test_regular_hit_overpower_does_not_apply_flurry();
    void test_regular_hit_mortal_strike_does_not_apply_flurry();

    void given_flurry_enabled();
    void given_flurry_is_not_active();
    void given_a_mainhand_and_offhand_equipped();

    void given_1_of_5_flurry();
    void given_2_of_5_flurry();
    void given_3_of_5_flurry();
    void given_4_of_5_flurry();
    void given_5_of_5_flurry();

    void when_flurry_is_applied();
    void when_flurry_is_removed();

    void when_performing_mh_attack();
    void when_performing_oh_attack();

    void when_performing_attack(Spell* spell);

    void then_flurry_is_active();
    void then_flurry_is_not_active();
};

#endif // TESTFLURRYWARRIOR_H
