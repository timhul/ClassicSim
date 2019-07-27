#include "TestCombat.h"

#include "Combat.h"
#include "Orc.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"

TestCombat::TestCombat(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "MID")
{}

void TestCombat::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Rogue(race, equipment_db, sim_settings, raid_control);
}

void TestCombat::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestCombat::test_spending_talent_points() {
    assert(!decrement("Lightning Reflexes"));

    assert(increment("Lightning Reflexes", 5));
    // 5 points
    assert(!increment("Lightning Reflexes"));
    assert(decrement("Lightning Reflexes"));
    assert(increment("Lightning Reflexes"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Deflection"));
    assert(!decrement("Lightning Reflexes"));
    assert(increment("Improved Gouge"));
    assert(decrement("Lightning Reflexes"));
    assert(!decrement("Lightning Reflexes"));
    assert(!decrement("Improved Gouge"));

    assert(increment("Lightning Reflexes"));
    assert(decrement("Improved Gouge"));
    assert(decrement("Deflection"));
    assert(decrement("Lightning Reflexes", 5));

    // 0 points spent, make Dual-Wield Specialization "available" via other talents
    assert(increment("Improved Gouge", 3));
    assert(increment("Improved Sinister Strike", 2));
    assert(increment("Improved Backstab", 3));
    assert(increment("Deflection", 5));
    assert(increment("Improved Sprint", 2));

    // Assert cannot spend points into Dual-Wield Specialization if 5/5 Precision is missing
    assert(!increment("Dual Wield Specialization"));
    assert(increment("Precision"));
    assert(!increment("Dual Wield Specialization"));
    assert(increment("Precision"));
    assert(!increment("Dual Wield Specialization"));
    assert(increment("Precision"));
    assert(!increment("Dual Wield Specialization"));
    assert(increment("Precision"));
    assert(!increment("Dual Wield Specialization"));
    assert(increment("Precision"));

    // Assert cannot remove points from Precision once points are spent in Dual-Wield Specialization
    assert(increment("Dual Wield Specialization"));
    assert(!decrement("Precision"));
    assert(increment("Dual Wield Specialization"));
    assert(!decrement("Precision"));
    assert(increment("Dual Wield Specialization"));
    assert(!decrement("Precision"));
    assert(increment("Dual Wield Specialization"));
    assert(!decrement("Precision"));
    assert(increment("Dual Wield Specialization"));
    assert(!decrement("Precision"));

    // 20 points spent
    assert(decrement("Dual Wield Specialization", 4));
    assert(decrement("Improved Backstab", 1));
    assert(tree_has_points(20));

    assert(increment("Blade Flurry"));

    // Cannot decrement lower tiers
    assert(!decrement("Dual Wield Specialization"));
    assert(!decrement("Improved Sprint"));
    assert(!decrement("Improved Backstab"));
    assert(!decrement("Lightning Reflexes"));

    // Try shifting points in T1
    assert(increment("Lightning Reflexes"));
    assert(decrement("Improved Sinister Strike"));
    assert(!decrement("Improved Sinister Strike"));
    assert(!decrement("Improved Gouge"));

    assert(increment("Improved Sinister Strike"));
    assert(decrement("Improved Gouge"));

    // Try shifting points in T3
    assert(increment("Riposte"));
    assert(decrement("Improved Sprint"));
    assert(!decrement("Riposte"));
    assert(!decrement("Improved Sprint"));

    assert(increment("Improved Sprint"));
    assert(decrement("Riposte"));

    // Try shifting points in T4
    assert(!decrement("Dual Wield Specialization"));
    assert(increment("Dagger Specialization"));
    assert(decrement("Dual Wield Specialization"));
    assert(!decrement("Dagger Specialization"));

    assert(increment("Dual Wield Specialization"));
    assert(decrement("Dagger Specialization"));

    // Assert cannot remove parent (Blade Flurry) when child (Weapon Expertise) is active although points allow
    assert(tree_has_points(21));
    assert(increment("Dagger Specialization", 4));
    assert(increment("Weapon Expertise"));
    assert(!decrement("Blade Flurry"));
    assert(increment("Weapon Expertise"));

    // Assert lower tiers cannot be decremented with Adrenaline Rush enabled (31 pts)
    assert(increment("Aggression", 3));
    assert(tree_has_points(30));
    assert(increment("Adrenaline Rush"));
    assert(!decrement("Dual Wield Specialization"));
    assert(!decrement("Improved Sprint"));
    assert(!decrement("Deflection"));
    assert(!decrement("Improved Sinister Strike"));

    assert(decrement("Adrenaline Rush"));
}

void TestCombat::test_clearing_tree_after_filling() {
    assert(increment("Improved Gouge", 3));
    assert(increment("Lightning Reflexes", 5));
    assert(increment("Improved Backstab", 3));
    assert(increment("Deflection", 5));
    assert(increment("Precision", 5));
    assert(increment("Endurance", 2));
    assert(increment("Improved Sprint", 2));
    assert(increment("Dual Wield Specialization", 5));
    assert(increment("Dagger Specialization", 5));
    assert(increment("Blade Flurry"));
    assert(increment("Weapon Expertise", 2));
    assert(increment("Adrenaline Rush"));

    assert(!decrement("Blade Flurry"));

    clear_tree();
}

void TestCombat::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_combat();
    assert(tree_has_points(37));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_combat();
    assert(tree_has_points(37));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_combat();
    assert(tree_has_points(37));
}

void TestCombat::spec_combat() {
    assert(increment("Improved Sinister Strike", 2));
    assert(increment("Improved Gouge", 3));
    assert(increment("Improved Backstab", 3));
    assert(increment("Precision", 5));
    assert(increment("Improved Sprint", 2));
    assert(increment("Dagger Specialization", 5));
    assert(increment("Dual Wield Specialization", 5));
    assert(increment("Sword Specialization", 5));
    assert(increment("Blade Flurry", 1));
    assert(increment("Weapon Expertise", 2));
    assert(increment("Aggression", 3));
    assert(increment("Adrenaline Rush", 1));
}
