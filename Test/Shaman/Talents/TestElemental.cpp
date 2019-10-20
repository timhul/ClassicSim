#include "TestElemental.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "Shaman.h"
#include "SimSettings.h"

TestElemental::TestElemental(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "LEFT")
{}

void TestElemental::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Shaman(race, equipment_db, sim_settings, raid_control);
}

void TestElemental::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestElemental::test_spending_talent_points() {
    assert(increment("Convection", 5));
    assert(increment("Concussion", 5));
    assert(increment("Reverberation", 5));
    assert(increment("Elemental Devastation", 3));
    assert(increment("Eye of the Storm", 3));
    assert(increment("Storm Reach", 2));
    assert(increment("Improved Fire Totems", 2));

    // Assert cannot spend points into Lightning Mastery if 5/5 Call of Thunder is missing
    assert(tree_has_points(25));

    assert(!increment("Lightning Mastery"));
    assert(increment("Call of Thunder"));
    assert(!increment("Lightning Mastery"));
    assert(increment("Call of Thunder"));
    assert(!increment("Lightning Mastery"));
    assert(increment("Call of Thunder"));
    assert(!increment("Lightning Mastery"));
    assert(increment("Call of Thunder"));
    assert(!increment("Lightning Mastery"));
    assert(increment("Call of Thunder"));
    assert(increment("Lightning Mastery"));

    // Assert cannot remove points from Call of Thunder once points are spent in Lightning Mastery
    assert(!decrement("Call of Thunder"));
    assert(decrement("Lightning Mastery"));
    assert(decrement("Call of Thunder"));
    assert(increment("Call of Thunder"));

    // Assert cannot increment Elemental Mastery without Elemental Fury
    assert(tree_has_points(30));

    assert(!increment("Elemental Mastery"));
    assert(increment("Elemental Fury"));
    assert(increment("Elemental Mastery"));
    assert(!decrement("Elemental Fury"));
}

void TestElemental::test_clearing_tree_after_filling() {
    spec_elemental();

    clear_tree();

    assert(tree_has_points(0));
}

void TestElemental::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_elemental();
    assert(tree_has_points(46));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_elemental();
    assert(tree_has_points(46));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_elemental();
    assert(tree_has_points(46));
}

void TestElemental::spec_elemental() {
    assert(increment("Convection", 5));
    assert(increment("Concussion", 5));
    assert(increment("Earth's Grasp", 2));
    assert(increment("Elemental Warding", 3));
    assert(increment("Call of Flame", 3));
    assert(increment("Elemental Focus", 1));
    assert(increment("Reverberation", 5));
    assert(increment("Call of Thunder", 5));
    assert(increment("Improved Fire Totems", 2));
    assert(increment("Eye of the Storm", 3));
    assert(increment("Elemental Devastation", 3));
    assert(increment("Storm Reach", 2));
    assert(increment("Elemental Fury", 1));
    assert(increment("Lightning Mastery", 5));
    assert(increment("Elemental Mastery", 1));
}
