#include "TestArcane.h"

#include <cassert>

#include "Mage.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Troll.h"

TestArcane::TestArcane(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "LEFT")
{}

void TestArcane::set_up() {
    race = new Troll();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Mage(race, equipment_db, sim_settings, raid_control);
}

void TestArcane::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestArcane::test_spending_talent_points() {
    assert(increment("Arcane Focus", 5));
    assert(increment("Improved Arcane Missiles", 5));
    assert(increment("Magic Absorption", 5));
    assert(increment("Arcane Concentration", 5));

    // Assert cannot spend points into Arcane Mind if 1/1 Arcane Resilience is missing
    assert(tree_has_points(20));

    assert(!increment("Arcane Mind"));
    assert(increment("Arcane Resilience"));
    assert(increment("Arcane Mind"));

    // Assert cannot remove points from Arcane Resilience once points are spent in Arcane Mind
    assert(!decrement("Arcane Resilience"));
    assert(decrement("Arcane Mind"));
    assert(decrement("Arcane Resilience"));

    // Assert cannot increment Arcane Power without Arcane Mind
    assert(increment("Arcane Resilience"));
    assert(increment("Arcane Mind", 5));
    assert(increment("Arcane Subtlety", 2));
    assert(increment("Magic Attunement", 2));
    assert(tree_has_points(30));

    assert(!increment("Arcane Power"));
    assert(!increment("Arcane Instability"));

    assert(increment("Presence of Mind"));
    assert(!increment("Arcane Power"));
    assert(increment("Arcane Instability"));
    assert(!decrement("Presence of Mind"));

    assert(increment("Arcane Instability", 2));
    assert(increment("Arcane Power"));
    assert(!decrement("Arcane Instability"));
}

void TestArcane::test_clearing_tree_after_filling() {
    spec_arcane();

    clear_tree();

    assert(tree_has_points(0));
}

void TestArcane::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_arcane();
    assert(tree_has_points(47));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_arcane();
    assert(tree_has_points(47));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_arcane();
    assert(tree_has_points(47));
}

void TestArcane::spec_arcane() {
    assert(increment("Arcane Subtlety", 2));
    assert(increment("Arcane Focus", 5));
    assert(increment("Improved Arcane Missiles", 5));
    assert(increment("Wand Specialization", 2));
    assert(increment("Magic Absorption", 5));
    assert(increment("Arcane Concentration", 5));
    assert(increment("Magic Attunement", 2));
    assert(increment("Improved Arcane Explosion", 3));
    assert(increment("Arcane Resilience", 1));
    assert(increment("Improved Mana Shield", 2));
    assert(increment("Improved Counterspell", 2));
    assert(increment("Arcane Meditation", 3));
    assert(increment("Presence of Mind", 1));
    assert(increment("Arcane Mind", 5));
    assert(increment("Arcane Instability", 3));
    assert(increment("Arcane Power", 1));
}
