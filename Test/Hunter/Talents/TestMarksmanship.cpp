#include "TestMarksmanship.h"

#include "Hunter.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestMarksmanship::TestMarksmanship(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "MID")
{}

void TestMarksmanship::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestMarksmanship::tear_down() {
    delete pchar;
    delete race;
    delete raid_control;
    delete sim_settings;
}

void TestMarksmanship::test_spending_talent_points() {
    assert(!decrement("Efficiency"));

    assert(increment("Efficiency", 5));
    // 5 points
    assert(!increment("Efficiency"));
    assert(decrement("Efficiency"));
    assert(increment("Efficiency"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Improved Hunter's Mark"));
    assert(!decrement("Efficiency"));
    assert(increment("Improved Concussive Shot"));
    assert(decrement("Efficiency"));
    assert(!decrement("Efficiency"));
    assert(!decrement("Improved Concussive Shot"));

    assert(increment("Efficiency"));
    assert(decrement("Improved Concussive Shot"));
    assert(increment("Improved Hunter's Mark", 4));

    // Make Mortal Shots available on raw points without fulfilling prerequisite Lethal Shots
    assert(tree_has_points(10));
    assert(increment("Improved Concussive Shot", 5));

    // Assert cannot spend points into Mortal Shots if 5/5 Lethal Shots is missing
    assert(!increment("Mortal Shots"));
    assert(increment("Lethal Shots"));
    assert(!increment("Mortal Shots"));
    assert(increment("Lethal Shots"));
    assert(!increment("Mortal Shots"));
    assert(increment("Lethal Shots"));
    assert(!increment("Mortal Shots"));
    assert(increment("Lethal Shots"));
    assert(!increment("Mortal Shots"));
    assert(increment("Lethal Shots"));
    assert(increment("Mortal Shots"));

    // Assert cannot remove points from Lethal Shots once points are spent in Mortal Shots
    assert(!decrement("Lethal Shots"));
    assert(increment("Mortal Shots"));
    assert(!decrement("Lethal Shots"));
    assert(increment("Mortal Shots"));
    assert(!decrement("Lethal Shots"));
    assert(increment("Mortal Shots"));
    assert(!decrement("Lethal Shots"));
    assert(increment("Mortal Shots"));
    assert(!decrement("Lethal Shots"));

    // Make Trueshot Aura available on raw points without fulfilling preprequisite Barrage
    assert(increment("Ranged Weapon Specialization", 5));

    // Assert cannot spend points into Trueshot Aura if 3/3 Barrage is missing
    assert(!increment("Trueshot Aura"));
    assert(increment("Barrage"));
    assert(!increment("Trueshot Aura"));
    assert(increment("Barrage"));
    assert(!increment("Trueshot Aura"));
    assert(increment("Barrage"));
    assert(increment("Trueshot Aura"));
}

void TestMarksmanship::test_clearing_tree_after_filling() {
    spec_marksmanship();

    clear_tree();

    assert(tree_has_points(0));
}

void TestMarksmanship::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_marksmanship();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_marksmanship();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_marksmanship();
    assert(tree_has_points(51));
}

void TestMarksmanship::spec_marksmanship() {
    assert(increment("Improved Concussive Shot", 5));
    assert(increment("Efficiency", 5));
    assert(increment("Improved Hunter's Mark", 5));
    assert(increment("Lethal Shots", 5));
    assert(increment("Aimed Shot"));
    assert(increment("Improved Arcane Shot", 5));
    assert(increment("Hawk Eye", 3));
    assert(increment("Improved Serpent Sting", 5));
    assert(increment("Mortal Shots", 5));
    assert(increment("Scatter Shot"));
    assert(increment("Barrage", 3));
    assert(increment("Improved Scorpid Sting", 3));
    assert(increment("Ranged Weapon Specialization", 4));
    assert(increment("Trueshot Aura"));
}

QString TestMarksmanship::get_position(const QString& name) const {
    if (name == "Improved Concussive Shot")
        return "1ML";
    if (name == "Efficiency")
        return "1MR";
    if (name == "Improved Hunter's Mark")
        return "2ML";
    if (name == "Lethal Shots")
        return "2MR";
    if (name == "Aimed Shot")
        return "3LL";
    if (name == "Improved Arcane Shot")
        return "3ML";
    if (name == "Hawk Eye")
        return "3RR";
    if (name == "Improved Serpent Sting")
        return "4ML";
    if (name == "Mortal Shots")
        return "4MR";
    if (name == "Scatter Shot")
        return "5LL";
    if (name == "Barrage")
        return "5ML";
    if (name == "Improved Scorpid Sting")
        return "5MR";
    if (name == "Ranged Weapon Specialization")
        return "6MR";
    if (name == "Trueshot Aura")
        return "7ML";

    return "";
}
