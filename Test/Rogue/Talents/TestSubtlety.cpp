#include "TestSubtlety.h"

#include "Orc.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "Subtlety.h"

TestSubtlety::TestSubtlety(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestSubtlety::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Rogue(race, equipment_db, sim_settings, raid_control);
}

void TestSubtlety::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestSubtlety::test_spending_talent_points() {
    assert(increment("Opportunity", 5));
    assert(increment("Sleight of Hand", 2));
    assert(increment("Elusiveness", 2));
    assert(increment("Camouflage", 1));
    assert(increment("Initiative", 3));
    assert(increment("Ghostly Strike", 1));
    assert(increment("Improved Ambush", 3));
    assert(increment("Setup", 2));
    assert(increment("Improved Sap", 3));

    // assert cannot increment Hemorrhage due to missing 3/3 Serrated Bldes
    assert(!increment("Hemorrhage"));
    assert(increment("Serrated Blades"));
    assert(!increment("Hemorrhage"));
    assert(increment("Serrated Blades"));
    assert(!increment("Hemorrhage"));
    assert(increment("Serrated Blades"));
    assert(increment("Hemorrhage"));

    assert(increment("Setup"));
    assert(increment("Deadliness", 3));

    // assert cannot increment Premeditation due to missing Preparation
    assert(tree_has_points(30));
    assert(!increment("Premeditation"));
    assert(increment("Preparation"));
    assert(increment("Premeditation"));
}

void TestSubtlety::test_clearing_tree_after_filling() {
    spec_hemo();

    assert(!decrement("Preparation"));
    assert(!decrement("Serrated Blades"));

    clear_tree();
}

void TestSubtlety::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_hemo();
    assert(tree_has_points(47));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_hemo();
    assert(tree_has_points(47));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_hemo();
    assert(tree_has_points(47));
}

void TestSubtlety::spec_hemo() {
    assert(increment("Master of Deception", 5));
    assert(increment("Opportunity", 5));
    assert(increment("Sleight of Hand", 2));
    assert(increment("Elusiveness", 2));
    assert(increment("Camouflage", 5));
    assert(increment("Initiative", 3));
    assert(increment("Ghostly Strike", 1));
    assert(increment("Improved Ambush", 3));
    assert(increment("Setup", 3));
    assert(increment("Improved Sap", 3));
    assert(increment("Serrated Blades", 3));
    assert(increment("Heightened Senses", 2));
    assert(increment("Preparation", 1));
    assert(increment("Dirty Deeds", 2));
    assert(increment("Hemorrhage", 1));
    assert(increment("Deadliness", 5));
    assert(increment("Premeditation", 1));
}
