
#include "TestSlam.h"
#include "Slam.h"
#include "Queue.h"
#include "ImprovedSlam.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "Equipment.h"

TestSlam::TestSlam(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Slam")
{}

void TestSlam::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_0_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_1_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_2_of_2_impale();
    tear_down();

    set_up();
    test_dodge_applies_overpower_buff();
    tear_down();

    set_up();
    test_cast_time_with_0_of_5_improved_slam();
    tear_down();

    set_up();
    test_cast_time_with_1_of_5_improved_slam();
    tear_down();

    set_up();
    test_cast_time_with_2_of_5_improved_slam();
    tear_down();

    set_up();
    test_cast_time_with_3_of_5_improved_slam();
    tear_down();

    set_up();
    test_cast_time_with_4_of_5_improved_slam();
    tear_down();

    set_up();
    test_cast_time_with_5_of_5_improved_slam();
    tear_down();

    set_up();
    test_auto_attacks_cancelled_during_slam_cast();
    tear_down();
}

Slam* TestSlam::slam() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_slam();
}

void TestSlam::test_name_correct() {
    assert(slam()->get_name() == "Slam");
}

void TestSlam::test_spell_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(slam()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestSlam::test_incurs_global_cooldown() {
    ImprovedSlam(pchar, nullptr).increment_rank();

    slam()->perform();

    then_next_event_is("CastComplete", "1.400");
    then_next_event_is("CooldownReady", "1.500");
}

void TestSlam::test_obeys_global_cooldown() {
    given_warrior_has_rage(100);
    assert(slam()->is_available());

    given_warrior_is_on_gcd();

    assert(!slam()->is_available());
    assert(delta(slam()->get_cooldown_remaining(), 0) < 0.0001);
}

void TestSlam::test_is_ready_conditions() {
    given_warrior_in_battle_stance();
    given_warrior_has_rage(100);
    assert(slam()->is_available());

    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(slam()->is_available());

    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    assert(slam()->is_available());
}

void TestSlam::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(15);

    when_slam_is_performed();

    then_warrior_has_rage(0);
}

void TestSlam::test_stance_cooldown() {
    given_warrior_has_rage(100);
    assert(slam()->is_available());

    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(!slam()->is_available());

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(!slam()->is_available());

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(slam()->is_available());
}

void TestSlam::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_slam_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_damage_bonus
    // [423] = 100 + (3.3 * 1000 / 14) + 87
    then_damage_dealt_is(423);
}

void TestSlam::test_crit_dmg_0_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_slam_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_damage_bonus
    // [845] = (100 + (3.3 * 1000 / 14) + 160) * 2.0
    then_damage_dealt_is(845);
}

void TestSlam::test_crit_dmg_1_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_slam_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [888] = (100 + (3.3 * 1000 / 14)) * 2.1
    then_damage_dealt_is(888);
}

void TestSlam::test_crit_dmg_2_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_slam_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) * crit_dmg_modifier
    // [930] = (100 + (3.3 * 1000 / 14)) * 2.2
    then_damage_dealt_is(930);
}

void TestSlam::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_slam_is_performed();

    then_overpower_is_active();
}

void TestSlam::test_cast_time_with_0_of_5_improved_slam() {
    assert(delta(slam()->get_cast_time(), 1.5) < 0.0001);
}

void TestSlam::test_cast_time_with_1_of_5_improved_slam() {
    ImprovedSlam(pchar, nullptr).increment_rank();

    assert(delta(slam()->get_cast_time(), 1.4) < 0.0001);
}

void TestSlam::test_cast_time_with_2_of_5_improved_slam() {
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();

    assert(delta(slam()->get_cast_time(), 1.3) < 0.0001);
}

void TestSlam::test_cast_time_with_3_of_5_improved_slam() {
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();

    assert(delta(slam()->get_cast_time(), 1.2) < 0.0001);
}

void TestSlam::test_cast_time_with_4_of_5_improved_slam() {
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();

    assert(delta(slam()->get_cast_time(), 1.1) < 0.0001);
}

void TestSlam::test_cast_time_with_5_of_5_improved_slam() {
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();

    assert(delta(slam()->get_cast_time(), 1.0) < 0.0001);
}

void TestSlam::test_auto_attacks_cancelled_during_slam_cast() {
    ImprovedSlam(pchar, nullptr).increment_rank();
    ImprovedSlam(pchar, nullptr).increment_rank();
    given_warrior_has_rage(100);
    given_a_mainhand_weapon_with_2_speed();
    given_an_offhand_weapon_with_3_speed();
    given_a_guaranteed_white_hit();

    pchar->start_attack();

    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("OffhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "0.100");
    then_next_event_is("PlayerAction", "0.100");

    given_engine_priority_at(1.0);

    assert(pchar->is_melee_attacking());
    slam()->perform();
    assert(!pchar->is_melee_attacking());

    then_next_event_is("MainhandMeleeHit", "2.000", RUN_EVENT);
    then_next_event_is("CastComplete", "2.300", RUN_EVENT);
    then_next_event_is("PlayerAction", "2.400");
    then_next_event_is("CooldownReady", "2.500");
    then_next_event_is("OffhandMeleeHit", "3.000", RUN_EVENT);
    then_next_event_is("MainhandMeleeHit", "4.300");
    then_next_event_is("OffhandMeleeHit", "5.300");
}

void TestSlam::when_slam_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    slam()->perform();

    while (pchar->get_engine()->get_current_priority() < 2.1) {
        if (pchar->get_engine()->get_queue()->empty()) {
            qDebug() << "Attempted to run queued events until 2.1"
                     << "but ran out of events at" << pchar->get_engine()->get_current_priority();
            assert(false);
        }
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (event->get_name() == "CastComplete") {
            event->act();
            delete event;
            break;
        }

        delete event;
    }
}
