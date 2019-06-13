#include "TestBeastMastery.h"

#include "Hunter.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestBeastMastery::TestBeastMastery(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "LEFT")
{}

void TestBeastMastery::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestBeastMastery::tear_down() {
    delete pchar;
    delete race;
    delete raid_control;
    delete sim_settings;
}

void TestBeastMastery::test_spending_talent_points() {
    assert(!decrement("Endurance Training"));

    assert(increment("Endurance Training", 5));
    // 5 points
    assert(!increment("Endurance Training"));
    assert(decrement("Endurance Training"));
    assert(increment("Endurance Training"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Improved Aspect of the Monkey"));
    assert(!decrement("Endurance Training"));
    assert(increment("Improved Aspect of the Hawk"));
    assert(decrement("Endurance Training"));
    assert(!decrement("Endurance Training"));
    assert(!decrement("Improved Aspect of the Hawk"));

    assert(increment("Endurance Training"));
    assert(decrement("Improved Aspect of the Hawk"));
    assert(increment("Improved Aspect of the Monkey", 4));

    // Assert cannot spend points into Frenzy if 5/5 Ferocity is missing
    assert(increment("Unleashed Fury", 5));
    assert(increment("Pathfinding", 2));
    assert(increment("Bestial Swiftness", 1));
    assert(increment("Improved Mend Pet", 2));
    assert(increment("Spirit Bond", 2));
    assert(increment("Bestial Discipline", 2));
    assert(increment("Improved Revive Pet"));
    assert(tree_has_points(25));

    assert(!increment("Frenzy"));
    assert(increment("Ferocity"));
    assert(!increment("Frenzy"));
    assert(increment("Ferocity"));
    assert(!increment("Frenzy"));
    assert(increment("Ferocity"));
    assert(!increment("Frenzy"));
    assert(increment("Ferocity"));
    assert(!increment("Frenzy"));
    assert(increment("Ferocity"));
    assert(increment("Frenzy"));
    assert(tree_has_points(31));
    assert(increment("Frenzy", 4));

    // Assert cannot remove points from Ferocity once points are spent in Frenzy
    assert(!decrement("Ferocity"));
    assert(decrement("Frenzy"));
    assert(!decrement("Ferocity"));
    assert(decrement("Frenzy"));
    assert(!decrement("Ferocity"));
    assert(decrement("Frenzy"));
    assert(!decrement("Ferocity"));
    assert(decrement("Frenzy"));
    assert(!decrement("Ferocity"));
    assert(decrement("Frenzy"));
    assert(!decrement("Frenzy"));
    assert(decrement("Ferocity"));
    assert(tree_has_points(29));

    // Assert cannot increment Bestial Wrath without Intimidation
    assert(increment("Ferocity"));
    assert(increment("Frenzy"));
    assert(tree_has_points(31));

    assert(!increment("Bestial Wrath"));
    assert(increment("Intimidation"));
    assert(increment("Bestial Wrath"));

    assert(decrement("Spirit Bond", 2));
    assert(tree_has_points(31));
    // Assert cannot decrement lower tiers
    assert(!decrement("Endurance Training"));
    assert(!decrement("Improved Aspect of the Monkey"));
    assert(!decrement("Unleashed Fury"));
    assert(!decrement("Ferocity"));
    assert(!decrement("Improved Mend Pet"));
    assert(!decrement("Bestial Discpline"));
    assert(!decrement("Frenzy"));
}

void TestBeastMastery::test_clearing_tree_after_filling() {
    spec_beast_mastery();

    clear_tree();

    assert(tree_has_points(0));
}

void TestBeastMastery::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_beast_mastery();
    assert(tree_has_points(48));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_beast_mastery();
    assert(tree_has_points(48));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_beast_mastery();
    assert(tree_has_points(48));
}

void TestBeastMastery::spec_beast_mastery() {
    assert(increment("Improved Aspect of the Hawk", 5));
    assert(increment("Endurance Training", 5));
    assert(increment("Improved Eyes of the Beast", 2));
    assert(increment("Improved Aspect of the Monkey", 5));
    assert(increment("Thick Hide", 3));
    assert(increment("Improved Revive Pet", 2));
    assert(increment("Pathfinding", 2));
    assert(increment("Bestial Swiftness", 1));
    assert(increment("Unleashed Fury", 5));
    assert(increment("Improved Mend Pet", 2));
    assert(increment("Ferocity", 5));
    assert(increment("Spirit Bond", 2));
    assert(increment("Intimidation", 1));
    assert(increment("Bestial Discipline", 2));
    assert(increment("Frenzy", 5));
    assert(increment("Bestial Wrath", 1));
}

QString TestBeastMastery::get_position(const QString& name) const {
    if (name == "Improved Aspect of the Hawk")
        return "1ML";
    if (name == "Endurance Training")
        return "1MR";
    if (name == "Improved Eyes of the Beast")
        return "2LL";
    if (name == "Improved Aspect of the Monkey")
        return "2ML";
    if (name == "Thick Hide")
        return "2MR";
    if (name == "Improved Revive Pet")
        return "2RR";
    if (name == "Pathfinding")
        return "3LL";
    if (name == "Bestial Swiftness")
        return "3ML";
    if (name == "Unleashed Fury")
        return "3MR";
    if (name == "Improved Mend Pet")
        return "4ML";
    if (name == "Ferocity")
        return "4MR";
    if (name == "Spirit Bond")
        return "5LL";
    if (name == "Intimidation")
        return "5ML";
    if (name == "Bestial Discipline")
        return "5RR";
    if (name == "Frenzy")
        return "6MR";
    if (name == "Bestial Wrath")
        return "7ML";

    return "";
}
