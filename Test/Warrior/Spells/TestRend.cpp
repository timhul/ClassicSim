#include "TestRend.h"

#include <cassert>

#include "Arms.h"
#include "Bloodthirst.h"
#include "ClassStatistics.h"
#include "Engine.h"
#include "Equipment.h"
#include "Event.h"
#include "HeroicStrike.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "Overpower.h"
#include "Queue.h"
#include "Rend.h"
#include "Talent.h"
#include "Whirlwind.h"

TestRend::TestRend(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Rend")
{}

void TestRend::test_all() {
    run_mandatory_tests();

    set_up();
    test_damage_of_0_of_3_improved_rend();
    tear_down();

    set_up();
    test_damage_of_1_of_3_improved_rend();
    tear_down();

    set_up();
    test_damage_of_2_of_3_improved_rend();
    tear_down();

    set_up();
    test_damage_of_3_of_3_improved_rend();
    tear_down();

    set_up();
    test_dodge_applies_overpower_buff();
    tear_down();
}

Rend* TestRend::rend() const {
    return static_cast<WarriorSpells*>(warrior->get_spells())->get_rend();
}

void TestRend::test_name_correct() {
    assert(rend()->get_name() == "Rend");
}

void TestRend::test_spell_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(rend()->get_base_cooldown(), 'f', 3) == "0.000");

    when_rend_is_performed();

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::DotTick, "3.000", RUN_EVENT);
    assert(rend()->get_spell_status() == SpellStatus::Available);
    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "9.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "12.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "15.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "18.000", RUN_EVENT);
}

void TestRend::test_whether_spell_causes_global_cooldown() {
    given_a_guaranteed_melee_ability_hit();

    assert(warrior->action_ready());
    when_rend_is_performed();
    assert(warrior->on_global_cooldown());

    then_next_event_is(EventType::PlayerAction, QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestRend::test_how_spell_observes_global_cooldown() {
    assert(rend()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(rend()->get_spell_status() == SpellStatus::OnGCD);
}

void TestRend::test_resource_cost() {
    given_warrior_has_rage(9);
    assert(rend()->get_spell_status() == SpellStatus::InsufficientResources);

    given_warrior_has_rage(10);
    assert(rend()->get_spell_status() == SpellStatus::Available);

    given_a_guaranteed_melee_ability_hit();

    when_rend_is_performed();

    then_warrior_has_rage(0);
}

void TestRend::test_is_ready_conditions() {
    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    assert(rend()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_battle_stance();
    given_warrior_has_rage(100);
    assert(rend()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(rend()->get_spell_status() == SpellStatus::InBerserkerStance);
}

void TestRend::test_stance_cooldown() {
    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    assert(rend()->get_spell_status() == SpellStatus::Available);

    when_switching_to_battle_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(rend()->get_spell_status() == SpellStatus::OnGCD);

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(rend()->get_spell_status() == SpellStatus::OnStanceCooldown);

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(rend()->get_spell_status() == SpellStatus::Available);
}

void TestRend::test_damage_of_0_of_3_improved_rend() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_0_of_3_improved_rend();
    given_no_previous_rend_damage_dealt();

    when_rend_is_performed();

    // total_rend_damage = (base_rend_damage + (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * duration * magic_value) * improved_rend_percent
    // [162] = (147 + (100 + (2.6 * 1000 / 14)) * 21 * 743/300000) * 1.0
    then_rend_damage_dealt_is(162);
    then_damage_is_dealt_over_21_seconds();
}

void TestRend::test_damage_of_1_of_3_improved_rend() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_1_of_3_improved_rend();
    given_no_previous_rend_damage_dealt();

    when_rend_is_performed();

    // total_rend_damage = (base_rend_damage + (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * duration * magic_value) * improved_rend_percent
    // [186] = (147 + (100 + (2.6 * 1000 / 14)) * 21 * 743/300000) * 1.15
    then_rend_damage_dealt_is(186);
    then_damage_is_dealt_over_21_seconds();
}

void TestRend::test_damage_of_2_of_3_improved_rend() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_2_of_3_improved_rend();
    given_no_previous_rend_damage_dealt();

    when_rend_is_performed();

    // total_rend_damage = (base_rend_damage + (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * duration * magic_value) * improved_rend_percent
    // [202] = (147 + (100 + (2.6 * 1000 / 14)) * 21 * 743/300000) * 1.25
    then_rend_damage_dealt_is(202);
    then_damage_is_dealt_over_21_seconds();
}

void TestRend::test_damage_of_3_of_3_improved_rend() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_3_of_3_improved_rend();
    given_no_previous_rend_damage_dealt();

    when_rend_is_performed();

    // total_rend_damage = (base_rend_damage + (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * duration * magic_value) * improved_rend_percent
    // [219] = (147 + (100 + (2.6 * 1000 / 14)) * 21 * 743/300000) * 1.35
    then_rend_damage_dealt_is(219);
    then_damage_is_dealt_over_21_seconds();
}

void TestRend::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_rend_is_performed();

    then_overpower_is_active();
}

void TestRend::given_0_of_3_improved_rend() {
}

void TestRend::given_1_of_3_improved_rend() {
    given_arms_talent_with_rank("Improved Rend", 1);
}

void TestRend::given_2_of_3_improved_rend() {
    given_arms_talent_with_rank("Improved Rend", 2);
}

void TestRend::given_3_of_3_improved_rend() {
    given_arms_talent_with_rank("Improved Rend", 3);
}

void TestRend::given_no_previous_rend_damage_dealt() {
    assert(pchar->get_statistics()->get_total_damage_for_spell("Rend") == 0);
}

void TestRend::when_rend_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    rend()->perform();
}

void TestRend::when_attack_is_performed(Spell* spell) {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    spell->perform();
}

void TestRend::then_rend_damage_dealt_is(const int damage_dealt) {
    while (!pchar->get_engine()->get_queue()->empty()) {
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (event->event_type != EventType::DotTick) {
            delete event;
            continue;
        }

        event->act();
        delete event;
    }

    if (pchar->get_statistics()->get_total_damage_for_spell("Rend") != damage_dealt)
        qDebug() << "Rend: expected" << damage_dealt << "got" << pchar->get_statistics()->get_total_damage_for_spell("Rend");
    assert(pchar->get_statistics()->get_total_damage_for_spell("Rend") == damage_dealt);
}

void TestRend::then_damage_is_dealt_over_21_seconds() {
    assert(QString::number(pchar->get_engine()->get_current_priority(), 'f', 3) == "21.000");
}
