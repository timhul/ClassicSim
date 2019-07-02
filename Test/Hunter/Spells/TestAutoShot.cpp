#include "TestAutoShot.h"

#include "AutoShot.h"
#include "Equipment.h"

TestAutoShot::TestAutoShot(EquipmentDb *equipment_db) :
    TestSpellHunter(equipment_db, "Auto Shot")
{}

void TestAutoShot::test_all() {
    run_mandatory_tests();

    set_up();
    test_changing_weapons_changes_cooldown();
    tear_down();

    set_up();
    test_dmg_affected_by_projectile_bonus();
    tear_down();

    set_up();
    test_hit_dmg_0_of_5_ranged_weapon_specialization();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_ranged_weapon_specialization();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_not_affected_by_1_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_not_affected_by_2_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_not_affected_by_3_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_not_affected_by_4_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_not_affected_by_5_of_5_mortal_shots();
    tear_down();

    set_up();
    test_crit_dmg_1_of_3_monster_slaying();
    tear_down();

    set_up();
    test_crit_dmg_2_of_3_monster_slaying();
    tear_down();

    set_up();
    test_crit_dmg_3_of_3_monster_slaying();
    tear_down();

    set_up();
    test_crit_dmg_1_of_3_humanoid_slaying();
    tear_down();

    set_up();
    test_crit_dmg_2_of_3_humanoid_slaying();
    tear_down();

    set_up();
    test_crit_dmg_3_of_3_humanoid_slaying();
    tear_down();

    set_up();
    test_mid_swing_haste_increase_updates_attack_speed();
    tear_down();

    set_up();
    test_mid_swing_haste_decrease_updates_attack_speed();
    tear_down();
}

AutoShot* TestAutoShot::auto_shot() const {
    auto* spells = dynamic_cast<HunterSpells*>(hunter->get_spells());
    return spells->get_auto_shot();
}

void TestAutoShot::test_name_correct() {
    assert(auto_shot()->get_name() == "Auto Shot");
}

void TestAutoShot::test_spell_cooldown() {
    given_a_ranged_weapon_with_3_speed();

    when_auto_shot_is_performed();

    then_next_expected_use_is(3.0);
}

void TestAutoShot::test_how_spell_observes_global_cooldown() {
    given_hunter_is_on_gcd();

    assert(auto_shot()->get_spell_status() == SpellStatus::Available);
}

void TestAutoShot::test_resource_cost() {
    given_hunter_has_mana(0);
    assert(auto_shot()->get_spell_status() == SpellStatus::Available);
}

void TestAutoShot::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestAutoShot::test_changing_weapons_changes_cooldown() {
    given_a_ranged_weapon_with_3_speed();
    when_auto_shot_is_performed();
    then_next_expected_use_is(3.0);

    when_changing_to_2_speed();
    when_auto_shot_is_performed();
    then_next_expected_use_is(2.0);
}

void TestAutoShot::test_whether_spell_causes_global_cooldown() {
    assert(hunter->action_ready());

    when_auto_shot_is_performed();

    assert(hunter->action_ready());
}

void TestAutoShot::test_dmg_affected_by_projectile_bonus() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    hunter->set_projectile_dps(20.0);

    when_auto_shot_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) + (projectile_dps * wpn_speed)
    // [338] = 100 + (2.6 * 1000 / 14) + (20.0 * 2.6)
    then_damage_dealt_is(338);
}

void TestAutoShot::test_hit_dmg_0_of_5_ranged_weapon_specialization() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_auto_shot_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14)
    // [286] = 100 + (2.6 * 1000 / 14)
    then_damage_dealt_is(286);
}

void TestAutoShot::test_hit_dmg_5_of_5_ranged_weapon_specialization() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_marksmanship_talent_rank("Ranged Weapon Specialization", 5);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * total_phys_modifier
    // [300] = (100 + (2.6 * 1000 / 14) * 1.05
    then_damage_dealt_is(300);
}

void TestAutoShot::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShot::test_crit_dmg_1_of_3_monster_slaying() {
    given_target_is_beast();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_survival_talent_rank("Monster Slaying", 1);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * total_phys_modifier
    // [580] = (100 + (2.6 * 1000 / 14)) * 2.01 * 1.01
    then_damage_dealt_is(580);
}

void TestAutoShot::test_crit_dmg_2_of_3_monster_slaying() {
    given_target_is_beast();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_survival_talent_rank("Monster Slaying", 2);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * total_phys_modifier
    // [589] = (100 + (2.6 * 1000 / 14)) * 2.02 * 1.02
    then_damage_dealt_is(589);
}

void TestAutoShot::test_crit_dmg_3_of_3_monster_slaying() {
    given_target_is_beast();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_survival_talent_rank("Monster Slaying", 3);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * total_phys_modifier
    // [597] = (100 + (2.6 * 1000 / 14)) * 2.03 * 1.03
    then_damage_dealt_is(597);
}

void TestAutoShot::test_crit_dmg_1_of_3_humanoid_slaying() {
    given_target_is_humanoid();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_survival_talent_rank("Humanoid Slaying", 1);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * total_phys_modifier
    // [580] = (100 + (2.6 * 1000 / 14)) * 2.01 * 1.01
    then_damage_dealt_is(580);
}

void TestAutoShot::test_crit_dmg_2_of_3_humanoid_slaying() {
    given_target_is_humanoid();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_survival_talent_rank("Humanoid Slaying", 2);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * total_phys_modifier
    // [589] = (100 + (2.6 * 1000 / 14)) * 2.02 * 1.02
    then_damage_dealt_is(589);
}

void TestAutoShot::test_crit_dmg_3_of_3_humanoid_slaying() {
    given_target_is_humanoid();
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_survival_talent_rank("Humanoid Slaying", 3);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * total_phys_modifier
    // [597] = (100 + (2.6 * 1000 / 14)) * 2.03 * 1.03
    then_damage_dealt_is(597);
}

void TestAutoShot::test_crit_dmg_not_affected_by_1_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_mortal_shots_rank(1);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShot::test_crit_dmg_not_affected_by_2_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_mortal_shots_rank(2);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShot::test_crit_dmg_not_affected_by_3_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_mortal_shots_rank(3);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShot::test_crit_dmg_not_affected_by_4_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_mortal_shots_rank(4);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShot::test_crit_dmg_not_affected_by_5_of_5_mortal_shots() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();
    given_mortal_shots_rank(5);

    when_auto_shot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShot::test_mid_swing_haste_increase_updates_attack_speed() {
    given_a_ranged_weapon_with_2_speed();
    when_auto_shot_is_performed();
    then_next_expected_use_is(2.0);
    given_engine_priority_at(1.0);

    when_increasing_attack_speed(100);

    then_next_expected_use_is(1.5);
}

void TestAutoShot::test_mid_swing_haste_decrease_updates_attack_speed() {
    given_a_ranged_weapon_with_3_speed();
    given_no_offhand();
    when_increasing_attack_speed(100);
    when_auto_shot_is_performed();
    then_next_expected_use_is(1.5);
    given_engine_priority_at(1.0);

    when_decreasing_attack_speed(100);

    then_next_expected_use_is(2.0);
}

void TestAutoShot::when_auto_shot_is_performed() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        given_a_ranged_weapon_with_100_min_max_dmg();

    auto_shot()->perform();
}

void TestAutoShot::when_changing_to_2_speed() {
    given_a_ranged_weapon_with_2_speed();
}

void TestAutoShot::when_increasing_attack_speed(const unsigned change) {
    hunter->increase_ranged_attack_speed(change);
}

void TestAutoShot::when_decreasing_attack_speed(const unsigned change) {
    hunter->decrease_ranged_attack_speed(change);
}

void TestAutoShot::then_next_expected_use_is(const double next_expected_use) {
    assert(almost_equal(next_expected_use, auto_shot()->get_next_expected_use()));
}
