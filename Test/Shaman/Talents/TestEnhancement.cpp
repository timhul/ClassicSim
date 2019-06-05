#include "TestEnhancement.h"

#include "Orc.h"
#include "RaidControl.h"
#include "Shaman.h"
#include "SimSettings.h"
#include "Target.h"

TestEnhancement::TestEnhancement(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "MID")
{}

void TestEnhancement::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    target = new Target(63);
    raid_control = new RaidControl(sim_settings);
    pchar = new Shaman(race, equipment_db, sim_settings, target, raid_control);
}

void TestEnhancement::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete target;
    delete raid_control;
}

void TestEnhancement::test_spending_talent_points() {
    assert(increment("Ancestral Knowledge", 5));
    assert(increment("Shield Specialization", 5));
    assert(increment("Anticipation", 5));

    // Assert cannot spend points into Flurry if 5/5 Thundering Strikes is missing
    assert(tree_has_points(15));

    assert(!increment("Flurry"));
    assert(increment("Thundering Strikes"));
    assert(!increment("Flurry"));
    assert(increment("Thundering Strikes"));
    assert(!increment("Flurry"));
    assert(increment("Thundering Strikes"));
    assert(!increment("Flurry"));
    assert(increment("Thundering Strikes"));
    assert(!increment("Flurry"));
    assert(increment("Thundering Strikes"));
    assert(increment("Flurry"));

    // Assert cannot remove points from Thundering Strikes once points are spent in Flurry
    assert(!decrement("Thundering Strikes"));
    assert(decrement("Flurry"));
    assert(decrement("Thundering Strikes"));
    assert(increment("Thundering Strikes"));

    // Assert cannot increment Stormstrike without Elemental Weapons
    assert(increment("Flurry", 5));
    assert(increment("Toughness", 5));
    assert(tree_has_points(30));

    assert(!increment("Stormstrike"));
    assert(increment("Elemental Weapons", 3));
    assert(increment("Stormstrike"));
    assert(!decrement("Elemental Weapons"));
}

void TestEnhancement::test_clearing_tree_after_filling() {
    spec_enhancement();

    clear_tree();

    assert(tree_has_points(0));
}

void TestEnhancement::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_enhancement();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_enhancement();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_enhancement();
    assert(tree_has_points(51));
}

void TestEnhancement::spec_enhancement() {
    assert(increment("Ancestral Knowledge", 5));
    assert(increment("Shield Specialization", 5));
    assert(increment("Guardian Totems", 2));
    assert(increment("Thundering Strikes", 5));
    assert(increment("Improved Ghost Wolf", 2));
    assert(increment("Improved Lightning Shield", 3));
    assert(increment("Enhancing Totems", 2));
    assert(increment("Two-Handed Axes and Maces", 1));
    assert(increment("Anticipation", 5));
    assert(increment("Flurry", 5));
    assert(increment("Toughness", 5));
    assert(increment("Improved Weapon Totems", 2));
    assert(increment("Elemental Weapons", 3));
    assert(increment("Parry", 1));
    assert(increment("Weapon Mastery", 4));
    assert(increment("Stormstrike", 1));
}

QString TestEnhancement::get_position(const QString& name) const {
    if (name == "Ancestral Knowledge")
        return "1ML";
    if (name == "Shield Specialization")
        return "1MR";
    if (name == "Guardian Totems")
        return "2LL";
    if (name == "Thundering Strikes")
        return "2ML";
    if (name == "Improved Ghost Wolf")
        return "2MR";
    if (name == "Improved Lightning Shield")
        return "2RR";
    if (name == "Enhancing Totems")
        return "3LL";
    if (name == "Two-Handed Axes and Maces")
        return "3MR";
    if (name == "Anticipation")
        return "3RR";
    if (name == "Flurry")
        return "4ML";
    if (name == "Toughness")
        return "4MR";
    if (name == "Improved Weapon Totems")
        return "5LL";
    if (name == "Elemental Weapons")
        return "5ML";
    if (name == "Parry")
        return "5MR";
    if (name == "Weapon Mastery")
        return "6MR";
    if (name == "Stormstrike")
        return "7ML";

    return "";
}
