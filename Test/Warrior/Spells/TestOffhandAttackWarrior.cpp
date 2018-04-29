
#include "TestOffhandAttackWarrior.h"
#include "Equipment.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include <QDebug>

void TestOffhandAttackWarrior::test_all() {
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
    test_hit_dmg_0_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_hit_dmg_1_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_hit_dmg_2_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_hit_dmg_3_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_hit_dmg_4_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_hit_dmg_5_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_crit_dmg_0_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_crit_dmg_1_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_crit_dmg_2_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_crit_dmg_3_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_crit_dmg_4_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_crit_dmg_5_of_5_dual_wield_specialization();
    tear_down();

    set_up();
    test_mid_swing_haste_increase_updates_attack_speed();
    tear_down();

    set_up();
    test_mid_swing_haste_decrease_updates_attack_speed();
    tear_down();
}

void TestOffhandAttackWarrior::test_name_correct() {
    assert(warrior->get_oh_attack()->get_name() == "Offhand Attack");
}

void TestOffhandAttackWarrior::test_has_weapon_speed_as_cooldown() {
    given_an_offhand_weapon_with_3_speed();

    when_oh_attack_is_performed();

    then_next_expected_use_is(3.0);
}

void TestOffhandAttackWarrior::test_changing_weapons_changes_cooldown() {
    given_an_offhand_weapon_with_3_speed();
    when_oh_attack_is_performed();
    then_next_expected_use_is(3.0);

    when_changing_to_2_speed();
    when_oh_attack_is_performed();
    then_next_expected_use_is(2.0);
}

void TestOffhandAttackWarrior::test_does_not_incur_global_cooldown_on_use() {
    assert(warrior->action_ready());

    when_oh_attack_is_performed();

    assert(warrior->action_ready());
}

void TestOffhandAttackWarrior::test_hit_dmg_0_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_hit();
    given_0_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * dual_wield_penalty
    // [143] = (100 + (2.6 * 1000 / 14)) * 0.5
    then_damage_dealt_is(143);
}

void TestOffhandAttackWarrior::test_hit_dmg_1_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_hit();
    given_1_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * dual_wield_penalty
    // [150] = (100 + (2.6 * 1000 / 14)) * 0.525
    then_damage_dealt_is(150);
}

void TestOffhandAttackWarrior::test_hit_dmg_2_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_hit();
    given_2_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * dual_wield_penalty
    // [157] = (100 + (2.6 * 1000 / 14)) * 0.55
    then_damage_dealt_is(157);
}

void TestOffhandAttackWarrior::test_hit_dmg_3_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_hit();
    given_3_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * dual_wield_penalty
    // [164] = (100 + (2.6 * 1000 / 14)) * 0.575
    then_damage_dealt_is(164);
}

void TestOffhandAttackWarrior::test_hit_dmg_4_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_hit();
    given_4_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * dual_wield_penalty
    // [171] = (100 + (2.6 * 1000 / 14)) * 0.6
    then_damage_dealt_is(171);
}

void TestOffhandAttackWarrior::test_hit_dmg_5_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_hit();
    given_5_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * dual_wield_penalty
    // [179] = (100 + (2.6 * 1000 / 14)) * 0.625
    then_damage_dealt_is(179);
}

void TestOffhandAttackWarrior::test_crit_dmg_0_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_crit();
    given_0_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * dual_wield_penalty
    // [286] = (100 + (2.6 * 1000 / 14)) * 2 * 0.5
    then_damage_dealt_is(286);
}

void TestOffhandAttackWarrior::test_crit_dmg_1_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_crit();
    given_1_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier* dual_wield_penalty
    // [300] = (100 + (2.6 * 1000 / 14)) * 2 * 0.525
    then_damage_dealt_is(300);
}

void TestOffhandAttackWarrior::test_crit_dmg_2_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_crit();
    given_2_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * dual_wield_penalty
    // [314] = (100 + (2.6 * 1000 / 14)) * 2 * 0.55
    then_damage_dealt_is(314);
}

void TestOffhandAttackWarrior::test_crit_dmg_3_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_crit();
    given_3_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier* dual_wield_penalty
    // [329] = (100 + (2.6 * 1000 / 14)) * 2 * 0.575
    then_damage_dealt_is(329);
}

void TestOffhandAttackWarrior::test_crit_dmg_4_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_crit();
    given_4_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * dual_wield_penalty
    // [343] = (100 + (2.6 * 1000 / 14)) * 2 * 0.6
    then_damage_dealt_is(343);
}

void TestOffhandAttackWarrior::test_crit_dmg_5_of_5_dual_wield_specialization() {
    given_a_guaranteed_white_crit();
    given_5_of_5_dual_wield_specialization();
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_oh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * crit_dmg_modifier * dual_wield_penalty
    // [357] = (100 + (2.6 * 1000 / 14)) * 2 * 0.625
    then_damage_dealt_is(357);
}

void TestOffhandAttackWarrior::test_mid_swing_haste_increase_updates_attack_speed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    when_mh_attack_is_performed();
    when_oh_attack_is_performed();
    then_next_expected_use_is(2.0);
    given_engine_priority_at(1.0);

    when_increasing_attack_speed(100);

    then_next_expected_use_is(1.5);
}

void TestOffhandAttackWarrior::test_mid_swing_haste_decrease_updates_attack_speed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_3_speed();
    when_increasing_attack_speed(100);
    when_mh_attack_is_performed();
    when_oh_attack_is_performed();
    given_engine_priority_at(1.0);

    when_decreasing_attack_speed(100);

    then_next_expected_use_is(2.0);
}

void TestOffhandAttackWarrior::given_0_of_5_dual_wield_specialization() {

}

void TestOffhandAttackWarrior::given_1_of_5_dual_wield_specialization() {
    warrior->get_oh_attack()->increase_effect_via_talent();
}

void TestOffhandAttackWarrior::given_2_of_5_dual_wield_specialization() {
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
}

void TestOffhandAttackWarrior::given_3_of_5_dual_wield_specialization() {
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
}

void TestOffhandAttackWarrior::given_4_of_5_dual_wield_specialization() {
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
}

void TestOffhandAttackWarrior::given_5_of_5_dual_wield_specialization() {
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
    warrior->get_oh_attack()->increase_effect_via_talent();
}

void TestOffhandAttackWarrior::when_mh_attack_is_performed() {
    warrior->get_mh_attack()->perform(0);
}

void TestOffhandAttackWarrior::when_oh_attack_is_performed() {
    warrior->get_oh_attack()->perform(0);
}

void TestOffhandAttackWarrior::when_changing_to_2_speed() {
    given_an_offhand_weapon_with_2_speed();
}

void TestOffhandAttackWarrior::when_increasing_attack_speed(const int change) {
    warrior->increase_attack_speed(change);
}

void TestOffhandAttackWarrior::when_decreasing_attack_speed(const int change) {
    warrior->decrease_attack_speed(change);
}

void TestOffhandAttackWarrior::then_next_expected_use_is(const float next_expected_use) {
    assert(QString::number(warrior->get_oh_attack()->get_next_expected_use(), 'f', 3) == QString::number(next_expected_use, 'f', 3));
}
