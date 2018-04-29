#ifndef TESTMAINHANDATTACKWARRIOR_H
#define TESTMAINHANDATTACKWARRIOR_H

#include "TestSpellWarrior.h"

class TestMainhandAttackWarrior: public TestSpellWarrior {
public:
    void test_all();

    void test_name_correct();
    void test_has_weapon_speed_as_cooldown();
    void test_changing_weapons_changes_cooldown();
    void test_does_not_incur_global_cooldown_on_use();

    void test_hit_dmg();
    void test_crit_dmg();

    void test_mid_swing_haste_increase_updates_attack_speed();
    void test_mid_swing_haste_decrease_updates_attack_speed();

    void when_mh_attack_is_performed();
    void when_changing_to_2_speed();
    void when_increasing_attack_speed(const int change);
    void when_decreasing_attack_speed(const int change);

    void then_next_expected_use_is(const float next_expected_use);

private:
};

#endif // TESTMAINHANDATTACKWARRIOR_H
