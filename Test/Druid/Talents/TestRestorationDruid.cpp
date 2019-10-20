#include "TestRestorationDruid.h"

#include <cassert>

#include "Druid.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Tauren.h"

TestRestorationDruid::TestRestorationDruid(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestRestorationDruid::set_up() {
    race = new Tauren();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Druid(race, equipment_db, sim_settings, raid_control);
}

void TestRestorationDruid::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestRestorationDruid::test_spending_talent_points() {

}

void TestRestorationDruid::test_clearing_tree_after_filling() {
    spec_restoration();

    clear_tree();

    assert(tree_has_points(0));
}

void TestRestorationDruid::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));
}

void TestRestorationDruid::spec_restoration() {
    assert(increment("Improved Mark of the Wild", 5));
    assert(increment("Furor", 5));
    assert(increment("Improved Healing Touch", 5));
    assert(increment("Nature's Focus", 5));
    assert(increment("Improved Enrage", 2));
    assert(increment("Reflection", 3));
    assert(increment("Insect Swarm", 1));
    assert(increment("Subtlety", 5));
    assert(increment("Tranquil Spirit", 5));
    assert(increment("Improved Rejuvenation", 3));
    assert(increment("Nature's Swiftness", 1));
    assert(increment("Gift of Nature", 5));
    assert(increment("Improved Tranquility", 2));
    assert(increment("Improved Regrowth", 4));

    assert(decrement("Improved Regrowth", 1));
    assert(increment("Swiftmend", 1));
}
