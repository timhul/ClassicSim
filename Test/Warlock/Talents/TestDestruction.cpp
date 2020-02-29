#include "TestDestruction.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warlock.h"

TestDestruction::TestDestruction(EquipmentDb* equipment_db_) : TestTalentTree(equipment_db_, "RIGHT") {}

void TestDestruction::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warlock(race, equipment_db, sim_settings, raid_control);
}

void TestDestruction::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestDestruction::test_spending_talent_points() {
    assert(increment("Improved Shadow Bolt", 5));
    assert(increment("Cataclysm", 5));
    assert(increment("Bane", 5));
    assert(increment("Aftermath", 5));
    assert(increment("Improved Searing Pain", 5));
    assert(increment("Emberstorm", 5));
    assert(tree_has_points(30));

    // Assert cannot spend points into Conflagrate if 5/5 Improved Immolate is missing
    assert(!increment("Conflagrate"));
    assert(increment("Improved Immolate", 4));
    assert(!increment("Conflagrate"));
    assert(increment("Improved Immolate"));
    assert(increment("Conflagrate"));

    // Assert cannot remove points from Improved Immolate once points are spent in Conflagrate
    assert(!decrement("Improved Immolate"));
    assert(decrement("Conflagrate"));
    assert(decrement("Improved Immolate", 5));
    assert(tree_has_points(30));

    // Assert cannot spend points into Ruin if 5/5 Devastation is missing
    assert(!increment("Ruin"));
    assert(increment("Devastation", 4));
    assert(!increment("Ruin"));
    assert(increment("Devastation"));
    assert(increment("Ruin"));

    // Assert cannot remove points from Devastation once points are spent in Ruin
    assert(!decrement("Devastation"));
    assert(decrement("Ruin"));
    assert(decrement("Devastation"));

    // Assert cannot increment Pyroclasm without 2/2 Intensity
    assert(!increment("Pyroclasm"));
    assert(increment("Intensity"));
    assert(!increment("Pyroclasm"));
    assert(increment("Intensity"));
    assert(increment("Pyroclasm"));

    assert(!decrement("Intensity"));
    assert(decrement("Pyroclasm"));
    assert(decrement("Intensity"));
}

void TestDestruction::test_clearing_tree_after_filling() {
    spec_destruction();

    clear_tree();

    assert(tree_has_points(0));
}

void TestDestruction::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_destruction();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_destruction();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_destruction();
    assert(tree_has_points(51));
}

void TestDestruction::spec_destruction() {
    assert(increment("Improved Shadow Bolt", 5));
    assert(increment("Cataclysm", 5));
    assert(increment("Bane", 5));
    assert(increment("Aftermath", 5));
    assert(increment("Improved Firebolt", 2));
    assert(increment("Improved Lash of Pain", 2));
    assert(increment("Devastation", 5));
    assert(increment("Shadowburn", 1));
    assert(increment("Intensity", 2));
    assert(increment("Destructive Reach", 2));
    assert(increment("Improved Searing Pain", 5));
    assert(increment("Pyroclasm", 2));
    assert(increment("Improved Immolate", 5));
    assert(increment("Ruin", 1));
    assert(increment("Emberstorm", 3));
    assert(increment("Conflagrate", 1));
}
