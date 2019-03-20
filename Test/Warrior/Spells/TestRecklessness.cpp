#include "TestRecklessness.h"

#include "CharacterStats.h"
#include "Equipment.h"
#include "MainhandAttackWarrior.h"
#include "Queue.h"
#include "Recklessness.h"
#include "Whirlwind.h"

TestRecklessness::TestRecklessness(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Recklessness")
{}

void TestRecklessness::test_all() {
    run_mandatory_tests();

    set_up();
    test_crit_reduced_after_buff_expires();
    tear_down();

    set_up();
    test_incurs_global_cooldown();
    tear_down();

    set_up();
    test_ability_miss_still_misses();
    tear_down();

    set_up();
    test_ability_dodge_still_dodges();
    tear_down();

    set_up();
    test_ability_parry_still_parries();
    tear_down();

    set_up();
    test_ability_block_still_blocks();
    tear_down();

    set_up();
    test_white_miss_still_misses();
    tear_down();

    set_up();
    test_white_dodge_still_dodges();
    tear_down();

    set_up();
    test_white_parry_still_parries();
    tear_down();

    set_up();
    test_white_block_still_blocks();
    tear_down();

    set_up();
    test_glancing_hits_converted_to_crits();
    tear_down();

    set_up();
    test_white_hit_converted_to_crit();
    tear_down();

    set_up();
    test_white_crit_still_crits();
    tear_down();

    set_up();
    test_ability_hit_converted_to_crit();
    tear_down();

    set_up();
    test_ability_crit_still_crits();
    tear_down();
}

Recklessness* TestRecklessness::recklessness() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_recklessness();
}

void TestRecklessness::test_name_correct() {
    assert(recklessness()->get_name() == "Recklessness");
}

void TestRecklessness::test_spell_cooldown() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(recklessness()->get_base_cooldown(), 'f', 3) == "1800.000");

    when_recklessness_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("BuffRemoval", "15.000");
    then_next_event_is("PlayerAction", "1800.000");
}

void TestRecklessness::test_obeys_global_cooldown() {
    given_warrior_in_berserker_stance();
    assert(recklessness()->is_available());

    given_warrior_is_on_gcd();

    assert(!recklessness()->is_available());
}

void TestRecklessness::test_is_ready_conditions() {
    given_warrior_has_rage(0);
    given_warrior_in_battle_stance();
    assert(warrior->action_ready());
    assert(!recklessness()->is_available());

    given_warrior_has_rage(100);
    assert(!recklessness()->is_available());

    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(recklessness()->is_available());
}

void TestRecklessness::test_stance_cooldown() {
    given_warrior_in_berserker_stance();
    assert(recklessness()->is_available());

    given_warrior_in_battle_stance();
    when_switching_to_berserker_stance();
    assert(warrior->on_stance_cooldown() == true);
    assert(!recklessness()->is_available());

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(!recklessness()->is_available());

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(recklessness()->is_available());
}

void TestRecklessness::test_crit_reduced_after_buff_expires() {
    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    when_recklessness_is_performed();
    assert(QString::number(int(round(pchar->get_stats()->get_mh_crit_chance() * 10000)), 'f', 3) == "10000.000");
    when_running_queued_events_until(15.01);

    if (dynamic_cast<Warrior*>(pchar)->in_berserker_stance())
        dynamic_cast<Warrior*>(pchar)->switch_to_battle_stance();

    assert(QString::number(int(round(pchar->get_stats()->get_mh_crit_chance() * 10000)), 'f', 3) == "0.000");
}

void TestRecklessness::test_incurs_global_cooldown() {
    when_recklessness_is_performed();

    then_next_event_is("PlayerAction", QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestRecklessness::test_resource_cost() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(0);

    when_recklessness_is_performed();

    then_warrior_has_rage(0);
}

void TestRecklessness::test_ability_miss_still_misses() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_miss();

    when_reck_and_whirlwind_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_ability_dodge_still_dodges() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_dodge();

    when_reck_and_whirlwind_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_ability_parry_still_parries() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_parry();

    when_reck_and_whirlwind_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_ability_block_still_blocks() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_block();

    when_reck_and_whirlwind_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_white_miss_still_misses() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_miss();

    when_reck_and_mh_attack_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_white_dodge_still_dodges() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_dodge();

    when_reck_and_mh_attack_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_white_parry_still_parries() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_parry();

    when_reck_and_mh_attack_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_white_block_still_blocks() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_block();

    when_reck_and_mh_attack_is_performed();

    then_damage_dealt_is(0);
}

void TestRecklessness::test_glancing_hits_converted_to_crits() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_white_glancing_blow();

    when_reck_and_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestRecklessness::test_white_hit_converted_to_crit() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_white_hit();

    when_reck_and_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestRecklessness::test_white_crit_still_crits() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_white_crit();

    when_reck_and_mh_attack_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) * crit_dmg_modifier
    // [571] = (100 + (2.6 * 1000 / 14)) * 2.0
    then_damage_dealt_is(571);
}

void TestRecklessness::test_ability_hit_converted_to_crit() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();

    when_reck_and_whirlwind_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [543] = (100 + (2.4 * 1000 / 14)) * 2.0
    then_damage_dealt_is(543);
}

void TestRecklessness::test_ability_crit_still_crits() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();

    when_reck_and_whirlwind_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [543] = (100 + (2.4 * 1000 / 14)) * 2.0
    then_damage_dealt_is(543);
}

void TestRecklessness::when_recklessness_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    recklessness()->perform();
}

void TestRecklessness::when_reck_and_mh_attack_is_performed() {
    when_recklessness_is_performed();
    then_next_event_is("PlayerAction", QString::number(warrior->global_cooldown(), 'f', 3));
    dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_mh_attack()->perform();
}

void TestRecklessness::when_reck_and_whirlwind_is_performed() {
    when_recklessness_is_performed();
    then_next_event_is("PlayerAction", QString::number(warrior->global_cooldown(), 'f', 3));
    dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind()->perform();
}
