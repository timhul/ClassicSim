#include "TestAutoShoot.h"

#include "AutoShoot.h"
#include "Equipment.h"

TestAutoShoot::TestAutoShoot(EquipmentDb *equipment_db) :
    TestSpellHunter(equipment_db, "Auto-Shoot")
{}

void TestAutoShoot::test_all() {
    run_mandatory_tests();

    set_up();
    test_changing_weapons_changes_cooldown();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_mid_swing_haste_increase_updates_attack_speed();
    tear_down();

    set_up();
    test_mid_swing_haste_decrease_updates_attack_speed();
    tear_down();
}

AutoShoot* TestAutoShoot::auto_shoot() {
    auto* spells = dynamic_cast<HunterSpells*>(hunter->get_spells());
    return spells->get_auto_shoot();
}

void TestAutoShoot::test_name_correct() {
    assert(auto_shoot()->get_name() == "Auto-Shoot");
}

void TestAutoShoot::test_spell_cooldown() {
    given_a_ranged_weapon_with_3_speed();

    when_auto_shoot_is_performed();

    then_next_expected_use_is(3.0);
}

void TestAutoShoot::test_obeys_global_cooldown() {
    given_hunter_is_on_gcd();

    assert(auto_shoot()->is_available());
}

void TestAutoShoot::test_resource_cost() {
    given_hunter_has_mana(0);
    assert(auto_shoot()->is_available());
}

void TestAutoShoot::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestAutoShoot::test_changing_weapons_changes_cooldown() {
    given_a_ranged_weapon_with_3_speed();
    when_auto_shoot_is_performed();
    then_next_expected_use_is(3.0);

    when_changing_to_2_speed();
    when_auto_shoot_is_performed();
    then_next_expected_use_is(2.0);
}

void TestAutoShoot::test_incurs_global_cooldown() {
    assert(hunter->action_ready());

    when_auto_shoot_is_performed();

    assert(hunter->action_ready());
}

void TestAutoShoot::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_auto_shoot_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14)
    // [286] = 100 + (2.6 * 1000 / 14)
    then_damage_dealt_is(286);
}

void TestAutoShoot::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_auto_shoot_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestAutoShoot::test_mid_swing_haste_increase_updates_attack_speed() {
    given_a_ranged_weapon_with_2_speed();
    when_auto_shoot_is_performed();
    then_next_expected_use_is(2.0);
    given_engine_priority_at(1.0);

    when_increasing_attack_speed(100);

    then_next_expected_use_is(1.5);
}

void TestAutoShoot::test_mid_swing_haste_decrease_updates_attack_speed() {
    given_a_ranged_weapon_with_3_speed();
    given_no_offhand();
    when_increasing_attack_speed(100);
    when_auto_shoot_is_performed();
    then_next_expected_use_is(1.5);
    given_engine_priority_at(1.0);

    when_decreasing_attack_speed(100);

    then_next_expected_use_is(2.0);
}

void TestAutoShoot::when_auto_shoot_is_performed() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        given_a_ranged_weapon_with_100_min_max_dmg();

    auto_shoot()->perform();
}

void TestAutoShoot::when_changing_to_2_speed() {
    given_a_ranged_weapon_with_2_speed();
}

void TestAutoShoot::when_increasing_attack_speed(const unsigned change) {
    hunter->increase_ranged_attack_speed(change);
}

void TestAutoShoot::when_decreasing_attack_speed(const unsigned change) {
    hunter->decrease_ranged_attack_speed(change);
}

void TestAutoShoot::then_next_expected_use_is(const double next_expected_use) {
    assert(almost_equal(next_expected_use, auto_shoot()->get_next_expected_use()));
}
