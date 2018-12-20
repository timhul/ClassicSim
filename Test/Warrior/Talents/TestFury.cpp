#include "Orc.h"
#include "TestFury.h"
#include "Warrior.h"

TestFury::TestFury(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "MID")
{}

void TestFury::set_up() {
    race = new Orc();
    pchar = new Warrior(race, equipment_db, nullptr);
}

void TestFury::tear_down() {
    delete pchar;
    delete race;
}

void TestFury::test_spending_talent_points() {
    assert(!decrement("Cruelty"));

    assert(increment("Cruelty", 5));
    // 5 points
    assert(!increment("Cruelty"));
    assert(decrement("Cruelty"));
    assert(increment("Cruelty"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("UW"));
    assert(!decrement("Cruelty"));
    assert(increment("BV"));
    assert(decrement("Cruelty"));
    assert(!decrement("Cruelty"));
    assert(!decrement("BV"));

    assert(increment("Cruelty"));
    assert(decrement("BV"));
    // 5 Cruelty 1 UW.

    assert(increment("UW", 4));
    assert(increment("Imp BS", 5));
    assert(increment("Enrage", 5));
    assert(increment("Death Wish"));

    // Cannot decrement lower tiers
    assert(!decrement("Imp BS"));
    assert(!decrement("Enrage"));
    assert(!decrement("UW"));
    assert(!decrement("Cruelty"));

    // Try shifting points in T1
    assert(increment("BV"));
    assert(decrement("Cruelty"));
    assert(!decrement("Cruelty"));
    assert(!decrement("BV"));

    assert(increment("Cruelty"));
    assert(decrement("BV"));

    // Try shifting points in T2
    assert(increment("Imp Demo"));
    assert(decrement("UW"));
    assert(!decrement("UW"));
    assert(!decrement("Imp Demo"));

    assert(increment("UW"));
    assert(decrement("Imp Demo"));

    // Try shifting points in T3
    assert(increment("Imp Cleave"));
    assert(decrement("Imp BS"));
    assert(!decrement("Imp Cleave"));
    assert(!decrement("Imp BS"));

    assert(increment("Imp BS"));
    assert(decrement("Imp Cleave"));

    // Try shifting points in T4
    assert(increment("Imp Execute"));
    assert(decrement("Enrage"));
    assert(!decrement("Imp Execute"));
    assert(!decrement("Enrage"));

    assert(increment("Enrage"));
    assert(decrement("Imp Execute"));

    assert(increment("DW Spec", 5));
    assert(increment("Flurry", 5));
    assert(increment("Imp Execute", 2));
    assert(increment("BT"));

    // Assert cannot remove parent (Death Wish) when child (BT) is active although points allow (34 spent)
    assert(!decrement("Death Wish"));

    // Assert lower tiers with only 5 points per tier cannot be decremented
    assert(!decrement("Imp BS"));
    assert(!decrement("UW"));
    assert(!decrement("Cruelty"));

    // Assert can decrement tier 4 to 31 (including BT) but not any lower
    assert(decrement("DW Spec"));
    assert(decrement("DW Spec"));
    assert(decrement("DW Spec"));
    assert(!decrement("DW Spec"));

    assert(decrement("BT"));
}

void TestFury::test_clearing_tree_after_filling() {
    assert(increment("BV", 5));
    assert(increment("Cruelty", 5));
    assert(increment("UW", 5));
    assert(increment("Imp BS", 5));
    assert(increment("Enrage", 5));
    assert(increment("Flurry", 5));
    assert(increment("Death Wish"));
    assert(increment("BT"));

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
    assert(increment("UW", 5));
    assert(increment("Imp BS", 5));
    assert(increment("DW Spec", 5));
    assert(increment("Enrage", 5));
    assert(increment("Flurry", 5));
    assert(increment("Imp Execute", 2));
    assert(increment("Death Wish"));
    assert(increment("BT"));
}

QString TestFury::get_position(const QString& name) const {
    if (name == "BV")
        return "1ML";
    if (name == "Cruelty")
        return "1MR";
    if (name == "Imp Demo")
        return "2ML";
    if (name == "UW")
        return "2MR";
    if (name == "Imp Cleave")
        return "3LL";
    if (name == "Piercing Howl")
        return "3ML";
    if (name == "Blood Craze")
        return "3MR";
    if (name == "Imp BS")
        return "3RR";
    if (name == "DW Spec")
        return "4LL";
    if (name == "Imp Execute")
        return "4ML";
    if (name == "Enrage")
        return "4MR";
    if (name == "Imp Slam")
        return "5LL";
    if (name == "Death Wish")
        return "5ML";
    if (name == "Imp Intercept")
        return "5RR";
    if (name == "Imp Zerker Rage")
        return "6LL";
    if (name == "Flurry")
        return "6MR";
    if (name == "BT")
        return "7ML";

    assert(false);
    return "";
}
