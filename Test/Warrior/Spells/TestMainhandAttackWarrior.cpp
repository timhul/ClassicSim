
#include "TestMainhandAttackWarrior.h"
#include "Equipment.h"
#include "MainhandAttackWarrior.h"
#include <QDebug>

void TestMainhandAttackWarrior::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_weapon_speed_as_cooldown();
    tear_down();

    set_up();
    test_changing_weapons_changes_cooldown();
    tear_down();

    set_up();
    test_does_not_incur_global_cooldown_on_use();
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

void TestMainhandAttackWarrior::test_name_correct() {
    assert(warrior->get_mh_attack()->get_name() == "Mainhand Attack");
}

void TestMainhandAttackWarrior::test_has_weapon_speed_as_cooldown() {
    given_a_mainhand_weapon_with_3_speed();

    when_mh_attack_is_performed();

    then_next_expected_use_is(3.0);
}

void TestMainhandAttackWarrior::test_changing_weapons_changes_cooldown() {
    given_a_mainhand_weapon_with_3_speed();
    when_mh_attack_is_performed();
    then_next_expected_use_is(3.0);

    when_changing_to_2_speed();
    when_mh_attack_is_performed();
    then_next_expected_use_is(2.0);
}

void TestMainhandAttackWarrior::test_does_not_incur_global_cooldown_on_use() {
    assert(warrior->action_ready());

    when_mh_attack_is_performed();

    assert(warrior->action_ready());
}

void TestMainhandAttackWarrior::test_hit_dmg() {
    given_a_guaranteed_white_hit();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14)
    // [286] = 100 + (2.6 * 1000 / 14)
    then_damage_dealt_is(286);
}

void TestMainhandAttackWarrior::test_crit_dmg() {
    given_a_guaranteed_white_crit();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestMainhandAttackWarrior::test_mid_swing_haste_increase_updates_attack_speed() {
    given_a_mainhand_weapon_with_2_speed();
    given_no_offhand();
    when_mh_attack_is_performed();
    then_next_expected_use_is(2.0);
    given_engine_priority_at(1.0);

    when_increasing_attack_speed(100);

    then_next_expected_use_is(1.5);
}

void TestMainhandAttackWarrior::test_mid_swing_haste_decrease_updates_attack_speed() {
    given_a_mainhand_weapon_with_3_speed();
    given_no_offhand();
    when_increasing_attack_speed(100);
    when_mh_attack_is_performed();
    then_next_expected_use_is(1.5);
    given_engine_priority_at(1.0);

    when_decreasing_attack_speed(100);

    then_next_expected_use_is(2.0);
}

void TestMainhandAttackWarrior::when_mh_attack_is_performed() {
    warrior->get_mh_attack()->perform(0);
}

void TestMainhandAttackWarrior::when_changing_to_2_speed() {
    given_a_mainhand_weapon_with_2_speed();
}

void TestMainhandAttackWarrior::when_increasing_attack_speed(const int change) {
    warrior->increase_attack_speed(change);
}

void TestMainhandAttackWarrior::when_decreasing_attack_speed(const int change) {
    warrior->decrease_attack_speed(change);
}

void TestMainhandAttackWarrior::then_next_expected_use_is(const float next_expected_use) {
    assert(QString::number(warrior->get_mh_attack()->get_next_expected_use(), 'f', 3) == QString::number(next_expected_use, 'f', 3));
}
