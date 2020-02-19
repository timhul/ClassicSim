#include "TestFury.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warrior.h"

TestFury::TestFury(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestFury::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
}

void TestFury::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestFury::test_spending_talent_points() {
    assert(!decrement("Cruelty"));

    assert(increment("Cruelty", 5));
    // 5 points
    assert(!increment("Cruelty"));
    assert(decrement("Cruelty"));
    assert(increment("Cruelty"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Unbridled Wrath"));
    assert(!decrement("Cruelty"));
    assert(increment("Booming Voice"));
    assert(decrement("Cruelty"));
    assert(!decrement("Cruelty"));
    assert(!decrement("Booming Voice"));

    assert(increment("Cruelty"));
    assert(decrement("Booming Voice"));
    // 5 Cruelty 1 UW.

    assert(increment("Unbridled Wrath", 4));
    assert(increment("Improved Battle Shout", 5));
    assert(increment("Enrage", 5));
    assert(increment("Death Wish"));

    // Cannot decrement lower tiers
    assert(!decrement("Improved Battle Shout"));
    assert(!decrement("Enrage"));
    assert(!decrement("Unbridled Wrath"));
    assert(!decrement("Cruelty"));

    // Try shifting points in T1
    assert(increment("Booming Voice"));
    assert(decrement("Cruelty"));
    assert(!decrement("Cruelty"));
    assert(!decrement("Booming Voice"));

    assert(increment("Cruelty"));
    assert(decrement("Booming Voice"));

    // Try shifting points in T2
    assert(increment("Improved Demoralizing Shout"));
    assert(decrement("Unbridled Wrath"));
    assert(!decrement("Unbridled Wrath"));
    assert(!decrement("Improved Demoralizing Shout"));

    assert(increment("Unbridled Wrath"));
    assert(decrement("Improved Demoralizing Shout"));

    // Try shifting points in T3
    assert(increment("Improved Cleave"));
    assert(decrement("Improved Battle Shout"));
    assert(!decrement("Improved Cleave"));
    assert(!decrement("Improved Battle Shout"));

    assert(increment("Improved Battle Shout"));
    assert(decrement("Improved Cleave"));

    // Try shifting points in T4
    assert(increment("Improved Execute"));
    assert(decrement("Enrage"));
    assert(!decrement("Improved Execute"));
    assert(!decrement("Enrage"));

    assert(increment("Enrage"));
    assert(decrement("Improved Execute"));

    assert(increment("Dual Wield Specialization", 5));
    assert(increment("Flurry", 5));
    assert(increment("Improved Execute", 2));
    assert(increment("Bloodthirst"));

    // Assert cannot remove parent (Death Wish) when child (BT) is active although points allow (34 spent)
    assert(!decrement("Death Wish"));

    // Assert lower tiers with only 5 points per tier cannot be decremented
    assert(!decrement("Improved Battle Shout"));
    assert(!decrement("Unbridled Wrath"));
    assert(!decrement("Cruelty"));

    // Assert can decrement tier 4 to 31 (including BT) but not any lower
    assert(decrement("Dual Wield Specialization"));
    assert(decrement("Dual Wield Specialization"));
    assert(decrement("Dual Wield Specialization"));
    assert(!decrement("Dual Wield Specialization"));

    assert(decrement("Bloodthirst"));
}

void TestFury::test_clearing_tree_after_filling() {
    assert(increment("Booming Voice", 5));
    assert(increment("Cruelty", 5));
    assert(increment("Unbridled Wrath", 5));
    assert(increment("Improved Battle Shout", 5));
    assert(increment("Enrage", 5));
    assert(increment("Flurry", 5));
    assert(increment("Death Wish"));
    assert(increment("Bloodthirst"));

    clear_tree();
}

void TestFury::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_dw_fury();
    assert(tree_has_points(34));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_dw_fury();
    assert(tree_has_points(34));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_dw_fury();
    assert(tree_has_points(34));
}

void TestFury::spec_dw_fury() {
    assert(increment("Cruelty", 5));
    assert(increment("Unbridled Wrath", 5));
    assert(increment("Improved Battle Shout", 5));
    assert(increment("Dual Wield Specialization", 5));
    assert(increment("Enrage", 5));
    assert(increment("Flurry", 5));
    assert(increment("Improved Execute", 2));
    assert(increment("Death Wish"));
    assert(increment("Bloodthirst"));
}
