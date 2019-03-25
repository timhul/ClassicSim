#ifndef TESTAUTOSHOT_H
#define TESTAUTOSHOT_H

#include "TestSpellHunter.h"

class AutoShot;

class TestAutoShot: public TestSpellHunter {
public:
    TestAutoShot(EquipmentDb *equipment_db);

    void test_all();

private:
    AutoShot* auto_shot();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_changing_weapons_changes_cooldown();
    void test_hit_dmg_0_of_5_ranged_weapon_specialization();
    void test_hit_dmg_5_of_5_ranged_weapon_specialization();
    void test_crit_dmg();
    void test_crit_dmg_1_of_3_monster_slaying();
    void test_crit_dmg_2_of_3_monster_slaying();
    void test_crit_dmg_3_of_3_monster_slaying();
    void test_crit_dmg_1_of_3_humanoid_slaying();
    void test_crit_dmg_2_of_3_humanoid_slaying();
    void test_crit_dmg_3_of_3_humanoid_slaying();
    void test_crit_dmg_not_affected_by_1_of_5_mortal_shots();
    void test_crit_dmg_not_affected_by_2_of_5_mortal_shots();
    void test_crit_dmg_not_affected_by_3_of_5_mortal_shots();
    void test_crit_dmg_not_affected_by_4_of_5_mortal_shots();
    void test_crit_dmg_not_affected_by_5_of_5_mortal_shots();

    void test_mid_swing_haste_increase_updates_attack_speed();
    void test_mid_swing_haste_decrease_updates_attack_speed();

    void when_auto_shot_is_performed();
    void when_changing_to_2_speed();
    void when_increasing_attack_speed(const unsigned change);
    void when_decreasing_attack_speed(const unsigned change);

    void then_next_expected_use_is(const double next_expected_use);
};

#endif // TESTAUTOSHOT_H
