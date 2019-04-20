#include "TestMainhandAttackWarrior.h"

#include "Equipment.h"
#include "MainhandAttackWarrior.h"

TestMainhandAttackWarrior::TestMainhandAttackWarrior(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "MainhandAttackWarrior")
{}

void TestMainhandAttackWarrior::test_all() {
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
    test_glancing_damage_300_wpn_skill();
    tear_down();

    set_up();
    test_glancing_damage_305_wpn_skill();
    tear_down();

    set_up();
    test_glancing_damage_310_wpn_skill();
    tear_down();

    set_up();
    test_glancing_damage_315_wpn_skill();
    tear_down();

    set_up();
    test_mid_swing_haste_increase_updates_attack_speed();
    tear_down();

    set_up();
    test_mid_swing_haste_decrease_updates_attack_speed();
    tear_down();

    set_up();
    test_dodge_applies_overpower_buff();
    tear_down();
}

MainhandAttackWarrior* TestMainhandAttackWarrior::mh_attack() {
    auto* spells = dynamic_cast<WarriorSpells*>(warrior->get_spells());
    return dynamic_cast<MainhandAttackWarrior*>(spells->get_mh_attack());
}

void TestMainhandAttackWarrior::test_name_correct() {
    assert(mh_attack()->get_name() == "Mainhand Attack");
}

void TestMainhandAttackWarrior::test_spell_cooldown() {
    given_a_mainhand_weapon_with_3_speed();

    when_mh_attack_is_performed();

    then_next_expected_use_is(3.0);
}

void TestMainhandAttackWarrior::test_obeys_global_cooldown() {
    assert(mh_attack()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(mh_attack()->get_spell_status() == SpellStatus::Available);
}

void TestMainhandAttackWarrior::test_resource_cost() {
    given_warrior_has_rage(0);
    assert(mh_attack()->get_spell_status() == SpellStatus::Available);
}

void TestMainhandAttackWarrior::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestMainhandAttackWarrior::test_stance_cooldown() {
    when_switching_to_berserker_stance();

    assert(warrior->on_stance_cooldown() == true);

    assert(mh_attack()->get_spell_status() == SpellStatus::Available);
}

void TestMainhandAttackWarrior::test_changing_weapons_changes_cooldown() {
    given_a_mainhand_weapon_with_3_speed();
    when_mh_attack_is_performed();
    then_next_expected_use_is(3.0);

    when_changing_to_2_speed();
    when_mh_attack_is_performed();
    then_next_expected_use_is(2.0);
}

void TestMainhandAttackWarrior::test_incurs_global_cooldown() {
    assert(warrior->action_ready());

    when_mh_attack_is_performed();

    assert(warrior->action_ready());
}

void TestMainhandAttackWarrior::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14)
    // [286] = 100 + (2.6 * 1000 / 14)
    then_damage_dealt_is(286);
}

void TestMainhandAttackWarrior::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestMainhandAttackWarrior::test_glancing_damage_300_wpn_skill() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_glancing_blow();
    given_300_weapon_skill_mh();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * glancing_dmg_modifier
    // [100] = (100 + (2.6 * 1000 / 14)) * 0.7
    then_damage_dealt_is(200);
}

void TestMainhandAttackWarrior::test_glancing_damage_305_wpn_skill() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_305_weapon_skill_mh();
    given_a_guaranteed_white_glancing_blow();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * glancing_dmg_modifier
    // [121] = (100 + (2.6 * 1000 / 14)) * 0.85
    then_damage_dealt_is(243);
}

void TestMainhandAttackWarrior::test_glancing_damage_310_wpn_skill() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_310_weapon_skill_mh();
    given_a_guaranteed_white_glancing_blow();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * glancing_dmg_modifier
    // [143] = (100 + (2.6 * 1000 / 14)) * 1.0
    then_damage_dealt_is(286);
}

void TestMainhandAttackWarrior::test_glancing_damage_315_wpn_skill() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_315_weapon_skill_mh();
    given_a_guaranteed_white_glancing_blow();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_mh_attack_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14)) * glancing_dmg_modifier
    // [143] = (100 + (2.6 * 1000 / 14)) * 1.0
    then_damage_dealt_is(286);
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

void TestMainhandAttackWarrior::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_white_dodge();

    when_mh_attack_is_performed();

    then_overpower_is_active();
}

void TestMainhandAttackWarrior::when_mh_attack_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    mh_attack()->perform();
}

void TestMainhandAttackWarrior::when_changing_to_2_speed() {
    given_a_mainhand_weapon_with_2_speed();
}

void TestMainhandAttackWarrior::when_increasing_attack_speed(const int change) {
    warrior->increase_melee_attack_speed(change);
}

void TestMainhandAttackWarrior::when_decreasing_attack_speed(const int change) {
    warrior->decrease_melee_attack_speed(change);
}

void TestMainhandAttackWarrior::then_next_expected_use_is(const double next_expected_use) {
    assert(QString::number(mh_attack()->get_next_expected_use(), 'f', 3) == QString::number(next_expected_use, 'f', 3));
}
