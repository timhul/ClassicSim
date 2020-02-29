#include "TestAffliction.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warlock.h"

TestAffliction::TestAffliction(EquipmentDb* equipment_db_) : TestTalentTree(equipment_db_, "LEFT") {}

void TestAffliction::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warlock(race, equipment_db, sim_settings, raid_control);
}

void TestAffliction::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestAffliction::test_spending_talent_points() {
    assert(increment("Suppression", 5));
    assert(increment("Improved Corruption", 5));
    assert(increment("Improved Curse of Weakness", 3));
    assert(increment("Improved Drain Soul", 2));
    assert(increment("Improved Drain Life", 5));

    // Assert cannot spend points into Curse of Exhaustion if 1/1 Amplify Curse is missing
    assert(tree_has_points(20));

    assert(!increment("Curse of Exhaustion"));
    assert(increment("Amplify Curse"));
    assert(increment("Curse of Exhaustion"));

    // Assert cannot remove points from Amplify Curse once points are spent in Curse of Exhaustion
    assert(!decrement("Amplify Curse"));
    assert(decrement("Curse of Exhaustion"));
    assert(decrement("Amplify Curse"));
    assert(tree_has_points(20));

    // Assert cannot spend points into Improved Curse of Exhaustion if 1/1 Curse of Exhaustion is missing
    assert(!increment("Improved Curse of Exhaustion"));
    assert(increment("Amplify Curse"));
    assert(!increment("Improved Curse of Exhaustion"));
    assert(increment("Curse of Exhaustion"));
    assert(increment("Improved Curse of Exhaustion"));

    // Assert cannot remove points from Curse of Exhaustion or Amplify Curse once points are spent in Improved Curse of Exhaustion
    assert(!decrement("Curse of Exhaustion"));
    assert(!decrement("Amplify Curse"));
    assert(decrement("Improved Curse of Exhaustion"));
    assert(decrement("Curse of Exhaustion"));
    assert(decrement("Amplify Curse"));

    // Assert cannot increment Shadow Mastery without Siphon Life
    assert(increment("Fel Concentration", 5));
    assert(tree_has_points(25));

    assert(!increment("Shadow Mastery"));
    assert(increment("Siphon Life"));
    assert(increment("Shadow Mastery"));

    assert(!decrement("Siphon Life"));
    assert(decrement("Shadow Mastery"));
    assert(decrement("Siphon Life"));
}

void TestAffliction::test_clearing_tree_after_filling() {
    spec_affliction();

    clear_tree();

    assert(tree_has_points(0));
}

void TestAffliction::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_affliction();
    assert(tree_has_points(49));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_affliction();
    assert(tree_has_points(49));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_affliction();
    assert(tree_has_points(49));
}

void TestAffliction::spec_affliction() {
    assert(increment("Suppression", 5));
    assert(increment("Improved Corruption", 5));
    assert(increment("Improved Curse of Weakness", 3));
    assert(increment("Improved Drain Soul", 2));
    assert(increment("Improved Life Tap", 2));
    assert(increment("Improved Drain Life", 5));
    assert(increment("Improved Curse of Agony", 3));
    assert(increment("Fel Concentration", 5));
    assert(increment("Amplify Curse", 1));
    assert(increment("Grim Reach", 2));
    assert(increment("Nightfall", 2));
    assert(increment("Improved Drain Mana", 2));
    assert(increment("Siphon Life", 1));
    assert(increment("Curse of Exhaustion", 1));
    assert(increment("Improved Curse of Exhaustion", 4));
    assert(increment("Shadow Mastery", 5));
    assert(increment("Dark Pact", 1));
}
