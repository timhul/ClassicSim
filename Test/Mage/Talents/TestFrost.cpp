#include "TestFrost.h"

#include "Mage.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Troll.h"

TestFrost::TestFrost(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestFrost::set_up() {
    race = new Troll();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Mage(race, equipment_db, sim_settings, raid_control);
}

void TestFrost::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestFrost::test_spending_talent_points() {
    assert(increment("Frost Warding", 2));
    assert(increment("Improved Frostbolt", 5));
    assert(increment("Elemental Precision", 3));
    assert(increment("Ice Shards", 5));

    // Assert cannot spend points into Shatter if 1/1 Improved Frost Nova is missing
    assert(tree_has_points(15));

    assert(!increment("Shatter"));
    assert(increment("Improved Frost Nova"));
    assert(!increment("Shatter"));
    assert(increment("Improved Frost Nova"));
    assert(increment("Shatter"));

    // Assert cannot remove points from Improved Frost Nova once points are spent in Shatter
    assert(!decrement("Improved Frost Nova"));
    assert(decrement("Shatter"));
    assert(decrement("Improved Frost Nova"));

    // Assert cannot increment Ice Barrier without Ice Block
    assert(increment("Improved Frost Nova"));
    assert(increment("Shatter", 5));
    assert(increment("Improved Cone of Cold", 3));
    assert(increment("Winter's Chill", 5));
    assert(tree_has_points(30));

    assert(!increment("Ice Barrier"));
    assert(increment("Ice Block"));
    assert(increment("Ice Barrier"));
    assert(!decrement("Ice Block"));
}

void TestFrost::test_clearing_tree_after_filling() {
    spec_frost();

    clear_tree();

    assert(tree_has_points(0));
}

void TestFrost::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_frost();
    assert(tree_has_points(50));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_frost();
    assert(tree_has_points(50));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_frost();
    assert(tree_has_points(50));
}

void TestFrost::spec_frost() {
    assert(increment("Frost Warding", 2));
    assert(increment("Improved Frostbolt", 5));
    assert(increment("Elemental Precision", 3));
    assert(increment("Ice Shards", 5));
    assert(increment("Frostbite", 3));
    assert(increment("Improved Frost Nova", 2));
    assert(increment("Permafrost", 3));
    assert(increment("Piercing Ice", 3));
    assert(increment("Cold Snap", 1));
    assert(increment("Improved Blizzard", 3));
    assert(increment("Arctic Reach", 2));
    assert(increment("Frost Channeling", 3));
    assert(increment("Shatter", 5));
    assert(increment("Ice Block", 1));
    assert(increment("Improved Cone of Cold", 3));
    assert(increment("Winter's Chill", 5));
    assert(increment("Ice Barrier", 1));
}

QString TestFrost::get_position(const QString& name) const {
    if (name == "Frost Warding")
        return "1LL";
    if (name == "Improved Frostbolt")
        return "1ML";
    if (name == "Elemental Precision")
        return "1MR";
    if (name == "Ice Shards")
        return "2LL";
    if (name == "Frostbite")
        return "2ML";
    if (name == "Improved Frost Nova")
        return "2MR";
    if (name == "Permafrost")
        return "2RR";
    if (name == "Piercing Ice")
        return "3LL";
    if (name == "Cold Snap")
        return "3ML";
    if (name == "Improved Blizzard")
        return "3RR";
    if (name == "Arctic Reach")
        return "4LL";
    if (name == "Frost Channeling")
        return "4ML";
    if (name == "Shatter")
        return "4MR";
    if (name == "Ice Block")
        return "5ML";
    if (name == "Improved Cone of Cold")
        return "5MR";
    if (name == "Winter's Chill")
        return "6MR";
    if (name == "Ice Barrier")
        return "7ML";

    return "";
}
