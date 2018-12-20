#include "Arms.h"
#include "Orc.h"
#include "TestArms.h"
#include "Warrior.h"

TestArms::TestArms(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "LEFT")
{}

void TestArms::set_up() {
    race = new Orc();
    pchar = new Warrior(race, equipment_db, nullptr);
}

void TestArms::tear_down() {
    delete pchar;
    delete race;
}

void TestArms::test_spending_talent_points() {
    assert(!decrement("Deflection"));

    assert(increment_talent_num_times("Deflection", 5));
    // 5 points
    assert(!increment("Deflection"));
    assert(decrement("Deflection"));
    assert(increment("Deflection"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Tactical Mastery"));
    assert(!decrement("Deflection"));
    assert(increment("Improved Rend"));
    assert(decrement("Deflection"));
    assert(!decrement("Deflection"));
    assert(!decrement("Improved Rend"));

    assert(increment("Deflection"));
    assert(decrement("Improved Rend"));
    // 5 Deflection 1 Imp TC.

    assert(increment_talent_num_times("Tactical Mastery", 4));

    // Assert cannot spend points into Deep Wounds if 3/3 Imp Rend is missing
    assert(!increment("Deep Wounds"));
    assert(increment("Improved Rend"));
    assert(!increment("Deep Wounds"));
    assert(increment("Improved Rend"));
    assert(!increment("Deep Wounds"));
    assert(increment("Improved Rend"));

    // Assert cannot remove points from Improved Rend once points are spent in Deep Wounds
    assert(increment("Deep Wounds"));
    assert(!decrement("Improved Rend"));
    assert(increment("Deep Wounds"));
    assert(!decrement("Improved Rend"));
    assert(increment("Deep Wounds"));
    assert(!decrement("Improved Rend"));


    assert(increment_talent_num_times("Improved Overpower", 2));
    assert(increment_talent_num_times("Impale", 2));
    assert(!decrement("Deep Wounds"));

    assert(increment("Sweeping Strikes"));

    // Cannot decrement lower tiers
    assert(!decrement("Impale"));
    assert(!decrement("Deep Wounds"));
    assert(!decrement("Tactical Mastery"));
    assert(!decrement("Deflection"));

    // Try shifting points in T1
    assert(increment("Improved Heroic Strike"));
    assert(decrement("Deflection"));
    assert(!decrement("Deflection"));
    assert(!decrement("Improved Heroic Strike"));

    assert(increment("Deflection"));
    assert(decrement("Improved Heroic Strike"));

    // Try shifting points in T2
    assert(increment("Improved Charge"));
    assert(decrement("Tactical Mastery"));
    assert(!decrement("Improved Charge"));
    assert(!decrement("Tactical Mastery"));

    assert(increment("Tactical Mastery"));
    assert(decrement("Improved Charge"));

    // Try shifting points in T3
    assert(increment("Anger Management"));
    assert(decrement("Improved Overpower"));
    assert(!decrement("Anger Management"));
    assert(!decrement("Improved Overpower"));

    assert(increment("Improved Overpower"));
    assert(decrement("Anger Management"));

    // Try shifting points in T4
    assert(increment("Two-Handed Weapon Specialization"));
    assert(decrement("Impale"));
    assert(!decrement("Two-Handed Weapon Specialization"));
    assert(!decrement("Two-Handed Weapon Specialization"));

    assert(increment("Impale"));
    assert(decrement("Two-Handed Weapon Specialization"));

    assert(increment_talent_num_times("Axe Specialization", 5));
    assert(increment("Two-Handed Weapon Specialization"));
    assert(!increment("Mortal Strike"));
    assert(increment("Two-Handed Weapon Specialization"));
    assert(!increment("Mortal Strike"));
    assert(increment("Two-Handed Weapon Specialization"));
    assert(!increment("Mortal Strike"));
    assert(increment("Two-Handed Weapon Specialization"));
    assert(tree_has_points(30));
    assert(increment("Mortal Strike"));

    // Assert cannot remove parent (Sweeping Strikes) when child (MS) is active although points allow
    assert(!decrement("Sweeping Strikes"));

    // Assert lower tiers cannot be decremented
    assert(!decrement("Axe Specialization"));
    assert(!decrement("Impale"));
    assert(!decrement("Deep Wounds"));
    assert(!decrement("Tactical Mastery"));
    assert(!decrement("Deflection"));

    assert(decrement("Mortal Strike"));
}

void TestArms::test_clearing_tree_after_filling() {
    assert(increment_talent_num_times("Deflection", 5));
    assert(increment_talent_num_times("Improved Rend", 3));
    assert(increment_talent_num_times("Tactical Mastery", 5));
    assert(increment_talent_num_times("Deep Wounds", 3));
    assert(increment("Anger Management"));
    assert(increment_talent_num_times("Impale", 2));
    assert(increment_talent_num_times("Two-Handed Weapon Specialization", 5));
    assert(increment_talent_num_times("Axe Specialization", 5));
    assert(increment("Sweeping Strikes"));
    assert(increment("Mortal Strike"));

    assert(!decrement("Two-Handed Weapon Specialization"));

    clear_tree();
}

void TestArms::test_refilling_tree_after_switching_talent_setup() {

}

QString TestArms::get_position(const QString& name) const {
    if (name == "Improved Heroic Strike")
        return "1LL";
    if (name == "Deflection")
        return "1ML";
    if (name == "Improved Rend")
        return "1MR";
    if (name == "Improved Charge")
        return "2LL";
    if (name == "Tactical Mastery")
        return "2ML";
    if (name == "Improved Thunder Clap")
        return "2RR";
    if (name == "Improved Overpower")
        return "3LL";
    if (name == "Anger Management")
        return "3ML";
    if (name == "Deep Wounds")
        return "3MR";
    if (name == "Two-Handed Weapon Specialization")
        return "4ML";
    if (name == "Impale")
        return "4MR";
    if (name == "Axe Specialization")
        return "5LL";
    if (name == "Sweeping Strikes")
        return "5ML";
    if (name == "Mace Specialization")
        return "5MR";
    if (name == "Sword Specialization")
        return "5RR";
    if (name == "Polearm Specialization")
        return "6LL";
    if (name == "Improved Hamstring")
        return "6MR";
    if (name == "Mortal Strike")
        return "7ML";

    assert(false);
    return "";
}
