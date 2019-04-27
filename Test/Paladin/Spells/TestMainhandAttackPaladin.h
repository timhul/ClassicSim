#ifndef TESTMAINHANDATTACKPALADIN_H
#define TESTMAINHANDATTACKPALADIN_H

#include "TestSpellPaladin.h"

class MainhandAttackPaladin;

class TestMainhandAttackPaladin: public TestSpellPaladin {
public:
    TestMainhandAttackPaladin(EquipmentDb *equipment_db);

    void test_all();

private:
    MainhandAttackPaladin* mh_attack();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_changing_weapons_changes_cooldown();
    void test_hit_dmg();
    void test_crit_dmg();
    void test_glancing_damage_300_wpn_skill();
    void test_glancing_damage_305_wpn_skill();
    void test_glancing_damage_310_wpn_skill();
    void test_glancing_damage_315_wpn_skill();
    void test_mid_swing_haste_increase_updates_attack_speed();
    void test_mid_swing_haste_decrease_updates_attack_speed();
    void test_seal_of_the_crusader_lowers_damage();

    void when_mh_attack_is_performed();
    void when_changing_to_2_speed();
    void when_increasing_attack_speed(const int change);
    void when_decreasing_attack_speed(const int change);

    void then_next_expected_use_is(const double next_expected_use);

    void given_seal_of_the_crusader_is_active();
};

#endif // TESTMAINHANDATTACKPALADIN_H
