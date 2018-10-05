#ifndef TESTOFFHANDATTACKWARRIOR_H
#define TESTOFFHANDATTACKWARRIOR_H

#include "TestSpellWarrior.h"

class OffhandAttackWarrior;

class TestOffhandAttackWarrior: public TestSpellWarrior {
public:
    TestOffhandAttackWarrior(EquipmentDb *equipment_db);

    void test_all();

    OffhandAttackWarrior* oh_attack();

    void test_name_correct();
    void test_has_weapon_speed_as_cooldown();
    void test_changing_weapons_changes_cooldown();
    void test_does_not_incur_global_cooldown_on_use();
    void test_hit_dmg_0_of_5_dual_wield_specialization();
    void test_hit_dmg_1_of_5_dual_wield_specialization();
    void test_hit_dmg_2_of_5_dual_wield_specialization();
    void test_hit_dmg_3_of_5_dual_wield_specialization();
    void test_hit_dmg_4_of_5_dual_wield_specialization();
    void test_hit_dmg_5_of_5_dual_wield_specialization();
    void test_crit_dmg_0_of_5_dual_wield_specialization();
    void test_crit_dmg_1_of_5_dual_wield_specialization();
    void test_crit_dmg_2_of_5_dual_wield_specialization();
    void test_crit_dmg_3_of_5_dual_wield_specialization();
    void test_crit_dmg_4_of_5_dual_wield_specialization();
    void test_crit_dmg_5_of_5_dual_wield_specialization();
    void test_glancing_damage_300_wpn_skill();
    void test_glancing_damage_305_wpn_skill();
    void test_glancing_damage_310_wpn_skill();
    void test_glancing_damage_315_wpn_skill();
    void test_mid_swing_haste_increase_updates_attack_speed();
    void test_mid_swing_haste_decrease_updates_attack_speed();
    void test_dodge_applies_overpower_buff();

    void given_0_of_5_dual_wield_specialization();
    void given_1_of_5_dual_wield_specialization();
    void given_2_of_5_dual_wield_specialization();
    void given_3_of_5_dual_wield_specialization();
    void given_4_of_5_dual_wield_specialization();
    void given_5_of_5_dual_wield_specialization();

    void when_mh_attack_is_performed();
    void when_oh_attack_is_performed();
    void when_changing_to_2_speed();
    void when_increasing_attack_speed(const int change);
    void when_decreasing_attack_speed(const int change);

    void then_next_expected_use_is(const double next_expected_use);

private:
};

#endif // TESTOFFHANDATTACKWARRIOR_H
