#include "TestEssenceOfTheRed.h"

#include <cassert>

#include "CharacterSpells.h"
#include "EncounterEnd.h"
#include "EncounterStart.h"
#include "Engine.h"
#include "Equipment.h"
#include "EssenceOfTheRed.h"
#include "Hunter.h"
#include "Orc.h"
#include "Queue.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "SpellRankGroup.h"
#include "Warrior.h"

TestEssenceOfTheRed::TestEssenceOfTheRed(EquipmentDb* _equipment_db) : TestSpell(_equipment_db, "Essence of the Red") {}

void TestEssenceOfTheRed::test_all() {
    qDebug() << spell_under_test;
    set_up_warrior();
    test_name_correct();
    tear_down();

    set_up_warrior();
    test_warrior_gains_rage_after_combat_start();
    tear_down();

    set_up_rogue();
    test_rogue_gains_energy_after_combat_start();
    tear_down();

    set_up_hunter();
    test_hunter_gains_mana_after_combat_start();
    tear_down();
}

void TestEssenceOfTheRed::test_name_correct() {
    assert(essence_of_the_red()->get_name() == "Essence of the Red");
}

void TestEssenceOfTheRed::test_hunter_gains_mana_after_combat_start() {
    given_vaelastrasz_ruleset_enabled();
    hunter->prepare_set_of_combat_iterations();
    Queue* queue = hunter->get_engine()->get_queue();
    queue->push(new EncounterStart(hunter->get_spells(), hunter->get_enabled_buffs()));
    queue->push(new EncounterEnd(hunter->get_engine(), 10));

    pchar->lose_mana(pchar->get_resource_level(ResourceType::Mana));
    then_resource_is(ResourceType::Mana, 0);

    given_event_is_ignored(EventType::PlayerAction);
    given_event_is_ignored(EventType::MainhandMeleeHit);
    given_event_is_ignored(EventType::OffhandMeleeHit);

    when_running_queued_events_until(1.5);
    then_resource_is(ResourceType::Mana, 500);
    when_running_queued_events_until(2.5);
    then_resource_is(ResourceType::Mana, 1000);
}

void TestEssenceOfTheRed::test_rogue_gains_energy_after_combat_start() {
    given_vaelastrasz_ruleset_enabled();
    rogue->prepare_set_of_combat_iterations();
    Queue* queue = rogue->get_engine()->get_queue();
    queue->push(new EncounterStart(rogue->get_spells(), rogue->get_enabled_buffs()));
    queue->push(new EncounterEnd(rogue->get_engine(), 10));

    pchar->lose_energy(100);
    then_resource_is(ResourceType::Energy, 0);

    given_event_is_ignored(EventType::PlayerAction);
    given_event_is_ignored(EventType::MainhandMeleeHit);
    given_event_is_ignored(EventType::OffhandMeleeHit);

    when_running_queued_events_until(1.5);
    then_resource_is(ResourceType::Energy, 50);
    when_running_queued_events_until(2.5);
    then_resource_is(ResourceType::Energy, 100);
}

void TestEssenceOfTheRed::test_warrior_gains_rage_after_combat_start() {
    given_vaelastrasz_ruleset_enabled();
    warrior->prepare_set_of_combat_iterations();
    Queue* queue = warrior->get_engine()->get_queue();
    queue->push(new EncounterStart(warrior->get_spells(), warrior->get_enabled_buffs()));
    queue->push(new EncounterEnd(warrior->get_engine(), 10));

    then_resource_is(ResourceType::Rage, 0);

    given_event_is_ignored(EventType::PlayerAction);
    given_event_is_ignored(EventType::MainhandMeleeHit);
    given_event_is_ignored(EventType::OffhandMeleeHit);

    when_running_queued_events_until(0.5);
    then_resource_is(ResourceType::Rage, 0);
    when_running_queued_events_until(1.5);
    then_resource_is(ResourceType::Rage, 20);
    when_running_queued_events_until(2.5);
    then_resource_is(ResourceType::Rage, 40);
    when_running_queued_events_until(3.5);
    then_resource_is(ResourceType::Rage, 60);
    when_running_queued_events_until(4.5);
    then_resource_is(ResourceType::Rage, 80);
    when_running_queued_events_until(5.5);
    then_resource_is(ResourceType::Rage, 100);
}

EssenceOfTheRed* TestEssenceOfTheRed::essence_of_the_red() const {
    assert(pchar->get_spells()->get_spell_rank_group_by_name("Essence of the Red") != nullptr);
    return static_cast<EssenceOfTheRed*>(pchar->get_spells()->get_spell_rank_group_by_name("Essence of the Red")->get_max_available_spell_rank());
}

void TestEssenceOfTheRed::set_up_general() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
}

void TestEssenceOfTheRed::set_up_hunter() {
    set_up_general();
    hunter = new Hunter(race, equipment_db, sim_settings, raid_control);
    pchar = hunter;
}

void TestEssenceOfTheRed::set_up_rogue() {
    set_up_general();
    rogue = new Rogue(race, equipment_db, sim_settings, raid_control);
    pchar = rogue;
}

void TestEssenceOfTheRed::set_up_warrior() {
    set_up_general();
    warrior = new Warrior(race, equipment_db, sim_settings, raid_control);
    pchar = warrior;
}

void TestEssenceOfTheRed::tear_down() {
    delete warrior;
    delete rogue;
    delete hunter;

    warrior = nullptr;
    rogue = nullptr;
    hunter = nullptr;

    delete race;
    delete sim_settings;
    delete raid_control;
}
