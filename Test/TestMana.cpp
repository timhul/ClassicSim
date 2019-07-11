#include "TestMana.h"

#include "CharacterStats.h"
#include "Event.h"
#include "Hunter.h"
#include "HunterSpells.h"
#include "MultiShot.h"
#include "Orc.h"

TestMana::TestMana(EquipmentDb* equipment_db) :
    TestSpellHunter(equipment_db, "Mana")
{}

void TestMana::test_all() {
    run_mandatory_tests();

    set_up();
    test_mana_gain_when_tick_is_within_5sr();
    tear_down();

    set_up();
    test_mana_gain_when_tick_is_outside_5sr();
    tear_down();
}

void TestMana::test_mana_gain_when_tick_is_within_5sr() {
    spend_mana();

    then_next_event_is(EventType::PlayerAction, "1.500");
    spend_mana();

    unsigned mana_before_tick = pchar->get_resource_level(ResourceType::Mana);
    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "2.100");
    then_next_event_is(EventType::PlayerAction, "3.000");
    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);

    unsigned gain_from_tick = pchar->get_resource_level(ResourceType::Mana) - mana_before_tick;
    // This will be zero until mp5 from gear is available.
    assert(gain_from_tick == 0);
}

void TestMana::test_mana_gain_when_tick_is_outside_5sr() {
    spend_mana();
    unsigned mana_before_tick = pchar->get_resource_level(ResourceType::Mana);

    then_next_event_is(EventType::PlayerAction, "1.500");
    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    assert((pchar->get_resource_level(ResourceType::Mana) - mana_before_tick) == 0);
    then_next_event_is(EventType::PlayerAction, "2.100");

    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    assert((pchar->get_resource_level(ResourceType::Mana) - mana_before_tick) == 0);
    then_next_event_is(EventType::PlayerAction, "4.100");

    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);

    unsigned gain_from_tick = pchar->get_resource_level(ResourceType::Mana) - mana_before_tick;
    // [Mana gain] = floor((base_mp5 + mp5_from_spirit) / 5 * 2) + remainder
    // 11 = floor((15 + (74 / 5)) / 5 * 2) + 0.0
    assert(pchar->get_stats()->get_spirit() == 74);
    assert(gain_from_tick == 11);

    // Remainder should be 0.92:
    // 0.92 = floor((15 + (74 / 5)) / 5 * 2)) - (15 + (74 / 5)) / 5 * 2)

    mana_before_tick = pchar->get_resource_level(ResourceType::Mana);
    then_next_event_is(EventType::PlayerAction, "6.100");
    then_next_event_is(EventType::DotTick, "8.000", RUN_EVENT);
    gain_from_tick = pchar->get_resource_level(ResourceType::Mana) - mana_before_tick;

    // [12] = floor((15 + (74 / 5) + 0.92) / 5 * 2) + 0.0
    assert(gain_from_tick == 12);
}

void TestMana::spend_mana() {
    given_a_guaranteed_ranged_white_hit();
    unsigned mana_before = pchar->get_resource_level(ResourceType::Mana);
    given_a_ranged_weapon_with_100_min_max_dmg();
    dynamic_cast<HunterSpells*>(hunter->get_spells())->get_multi_shot()->perform();
    assert(mana_before - pchar->get_resource_level(ResourceType::Mana) == 230);
}

void TestMana::test_name_correct() {
}

void TestMana::test_spell_cooldown() {
}

void TestMana::test_how_spell_observes_global_cooldown() {
}

void TestMana::test_resource_cost() {
}

void TestMana::test_is_ready_conditions() {
}

void TestMana::test_whether_spell_causes_global_cooldown() {
}
