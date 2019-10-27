#include "TestEnergy.h"

#include <cassert>

#include "Event.h"
#include "Rogue.h"
#include "Vigor.h"

TestEnergy::TestEnergy(EquipmentDb* equipment_db) :
    TestSpell(equipment_db, "Energy"),
    rogue(nullptr)
{}

void TestEnergy::set_up() {
    set_up_general();
    rogue = new Rogue(race, equipment_db, sim_settings, raid_control);
    rogue->set_clvl(60);
    pchar = rogue;
}

void TestEnergy::tear_down() {
    delete rogue;
    tear_down_general();
}

void TestEnergy::test_all() {
    qDebug() << "TestEnergy";
    set_up();
    test_energy_ticks_up_after_use();
    tear_down();

    set_up();
    test_energy_tick_adds_player_action_event();
    tear_down();

    set_up();
    test_losing_energy_while_non_max_does_not_change_energy_tick_timer();
    tear_down();

    set_up();
    test_energy_tick_timer_is_pushed_forward_if_completed_before_losing_energy_again();
    tear_down();

    set_up();
    test_only_single_resource_gain_is_queued();
    tear_down();

    set_up();
    test_vigor_changes_max_energy();
    tear_down();
}

void TestEnergy::test_energy_ticks_up_after_use() {
    then_rogue_has_energy(100);
    rogue->lose_energy(75);
    then_rogue_has_energy(25);
    given_event_is_ignored(EventType::PlayerAction);

    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_rogue_has_energy(45);

    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    then_rogue_has_energy(65);

    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    then_rogue_has_energy(85);

    then_next_event_is(EventType::DotTick, "8.000", RUN_EVENT);
    then_rogue_has_energy(100);

    then_next_event_is(EventType::DotTick, "10.000", RUN_EVENT);
    then_rogue_has_energy(100);
}

void TestEnergy::test_energy_tick_adds_player_action_event() {
    rogue->lose_energy(75);

    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "2.100");
    then_next_event_is(EventType::DotTick, "4.000");
}

void TestEnergy::test_losing_energy_while_non_max_does_not_change_energy_tick_timer() {
    rogue->lose_energy(75);

    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "2.100");
    then_rogue_has_energy(45);

    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "4.100");
    then_rogue_has_energy(65);

    given_engine_priority_at(5.0);
    rogue->lose_energy(60);
    then_rogue_has_energy(5);

    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "6.100");
    then_rogue_has_energy(25);

    then_next_event_is(EventType::DotTick, "8.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "8.100");
    then_rogue_has_energy(45);

    then_next_event_is(EventType::DotTick, "10.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "10.100");
    then_rogue_has_energy(65);

    then_next_event_is(EventType::DotTick, "12.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "12.100");
    then_rogue_has_energy(85);

    then_next_event_is(EventType::DotTick, "14.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "14.100");
    then_rogue_has_energy(100);

    then_next_event_is(EventType::DotTick, "16.000", RUN_EVENT);
    then_rogue_has_energy(100);
}

void TestEnergy::test_energy_tick_timer_is_pushed_forward_if_completed_before_losing_energy_again() {
    rogue->lose_energy(10);

    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "2.100");
    then_rogue_has_energy(100);

    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    then_rogue_has_energy(100);

    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    given_engine_priority_at(7.5);
    rogue->lose_energy(10);

    then_next_event_is(EventType::DotTick, "9.500", RUN_EVENT);
    then_next_event_is(EventType::PlayerAction, "9.600");
    then_rogue_has_energy(100);

    then_next_event_is(EventType::DotTick, "11.500", RUN_EVENT);
    then_rogue_has_energy(100);
}

void TestEnergy::test_only_single_resource_gain_is_queued() {
    given_event_is_ignored(EventType::PlayerAction);
    rogue->lose_energy(10);
    rogue->gain_energy(10);
    rogue->lose_energy(100);

    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "8.000", RUN_EVENT);
}

void TestEnergy::test_vigor_changes_max_energy() {
    auto vigor = Vigor(rogue, nullptr);
    then_rogue_has_energy(100);

    assert(vigor.increment_rank());
    then_rogue_has_energy(110);

    assert(vigor.decrement_rank());
    then_rogue_has_energy(100);
}

void TestEnergy::then_rogue_has_energy(const unsigned energy) const {
    if (energy != rogue->get_resource_level(ResourceType::Energy))
        qDebug() << "Expected" << energy << "energy but actually has" << rogue->get_resource_level(ResourceType::Energy);
    assert(rogue->get_resource_level(ResourceType::Energy) == energy);
}
