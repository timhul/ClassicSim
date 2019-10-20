#include "TestRetribution.h"

#include <cassert>

#include "Human.h"
#include "Paladin.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestRetribution::TestRetribution(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestRetribution::set_up() {
    race = new Human();
    raid_control = new RaidControl(sim_settings);
    pchar = new Paladin(race, equipment_db, sim_settings, raid_control);
}

void TestRetribution::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestRetribution::test_spending_talent_points() {
    // Assert cannot spend points into Vengeance if 5/5 Conviction missing
    assert(increment("Improved Blessing of Might", 5));
    assert(increment("Benediction", 5));
    assert(increment("Deflection", 5));
    assert(increment("Conviction", 4));
    assert(increment("Improved Retribution Aura", 2));
    assert(increment("Two-Handed Weapon Specialization", 3));
    assert(increment("Sanctity Aura"));

    assert(tree_has_points(25));
    assert(!increment("Vengeance"));
    assert(increment("Conviction"));
    assert(increment("Vengeance"));
    assert(!decrement("Conviction"));
}

void TestRetribution::test_clearing_tree_after_filling() {
    spec_retribution();

    clear_tree();

    assert(tree_has_points(0));
}

void TestRetribution::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_retribution();
    assert(tree_has_points(45));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_retribution();
    assert(tree_has_points(45));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_retribution();
    assert(tree_has_points(45));
}

void TestRetribution::spec_retribution() {
    assert(increment("Improved Blessing of Might", 5));
    assert(increment("Benediction", 5));
    assert(increment("Improved Judgement", 2));
    assert(increment("Improved Seal of the Crusader", 3));
    assert(increment("Deflection", 5));
    assert(increment("Vindication", 3));
    assert(increment("Conviction", 5));
    assert(increment("Seal of Command", 1));
    assert(increment("Pursuit of Justice", 2));
    assert(increment("Eye for an Eye", 2));
    assert(increment("Improved Retribution Aura", 2));
    assert(increment("Two-Handed Weapon Specialization", 3));
    assert(increment("Sanctity Aura", 1));
    assert(increment("Vengeance", 5));
    assert(increment("Repentance", 1));
}
