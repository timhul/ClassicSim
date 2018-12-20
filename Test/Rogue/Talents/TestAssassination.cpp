#include "TestAssassination.h"

#include "Assassination.h"
#include "Orc.h"
#include "Rogue.h"

TestAssassination::TestAssassination(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "LEFT")
{}

void TestAssassination::set_up() {
    race = new Orc();
    pchar = new Rogue(race, equipment_db, nullptr);
}

void TestAssassination::tear_down() {
    delete pchar;
    delete race;
}

void TestAssassination::test_spending_talent_points() {
    assert(!decrement("Malice"));

    assert(increment("Malice", 5));
    // 5 points
    assert(!increment("Malice"));
    assert(decrement("Malice"));
    assert(increment("Malice"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Murder"));
    assert(!decrement("Malice"));
    assert(increment("Improved Eviscerate"));
    assert(decrement("Malice"));
    assert(!decrement("Malice"));
    assert(!decrement("Improved Eviscerate"));

    assert(increment("Malice"));
    assert(decrement("Improved Eviscerate"));
    assert(decrement("Murder"));
    assert(decrement("Malice", 5));

    // 0 points spent, make Lethality "available" via other talents
    assert(increment("Improved Eviscerate", 3));
    assert(increment("Remorseless Attacks", 2));
    assert(increment("Ruthlessness", 3));
    assert(increment("Murder", 2));

    // Assert cannot spend points into Lethality if 5/5 Malice is missing
    assert(!increment("Lethality"));
    assert(increment("Malice"));
    assert(!increment("Lethality"));
    assert(increment("Malice"));
    assert(!increment("Lethality"));
    assert(increment("Malice"));
    assert(!increment("Lethality"));
    assert(increment("Malice"));
    assert(!increment("Lethality"));
    assert(increment("Malice"));

    // Assert cannot remove points from Malice once points are spent in Lethality
    assert(increment("Lethality"));
    assert(!decrement("Malice"));
    assert(increment("Lethality"));
    assert(!decrement("Malice"));
    assert(increment("Lethality"));
    assert(!decrement("Malice"));
    assert(increment("Lethality"));
    assert(!decrement("Malice"));
    assert(increment("Lethality"));
    assert(!decrement("Malice"));

    // 20 points spent, shift around points in T1 into T4 for assertions.
    assert(increment("Vile Poisons", 3));
    assert(decrement("Improved Eviscerate", 3));
    assert(tree_has_points(20));

    assert(increment("Cold Blood"));

    // Cannot decrement lower tiers
    assert(!decrement("Vile Poisons"));
    assert(!decrement("Lethality"));
    assert(!decrement("Ruthlessness"));
    assert(!decrement("Malice"));

    // Try shifting points in T1
    assert(increment("Improved Eviscerate"));
    assert(decrement("Remorseless Attacks"));
    assert(!decrement("Remorseless Attacks"));
    assert(!decrement("Improved Eviscerate"));

    assert(increment("Remorseless Attacks"));
    assert(decrement("Improved Eviscerate"));

    // Try shifting points in T2
    assert(increment("Improved Slice and Dice"));
    assert(decrement("Murder"));
    assert(!decrement("Improved Slice and Dice"));
    assert(!decrement("Murder"));

    assert(increment("Murder"));
    assert(decrement("Improved Slice and Dice"));

    // Try shifting points in T3
    assert(increment("Improved Expose Armor"));
    assert(decrement("Lethality"));
    assert(!decrement("Improved Expose Armor"));
    assert(!decrement("Lethality"));

    assert(increment("Lethality"));
    assert(decrement("Improved Expose Armor"));

    // Try shifting points in T4
    assert(!decrement("Vile Poisons"));
    assert(increment("Improved Poisons"));
    assert(decrement("Vile Poisons"));
    assert(!decrement("Improved Poisons"));

    assert(increment("Vile Poisons"));
    assert(decrement("Improved Poisons"));

    // Assert cannot remove parent (Cold Blood) when child (Seal Fate) is active although points allow
    assert(increment("Improved Poisons", 5));
    assert(increment("Vile Poisons", 2));
    assert(tree_has_points(28));
    assert(increment("Seal Fate"));
    assert(!decrement("Cold Blood"));
    assert(increment("Seal Fate"));

    // Assert lower tiers cannot be decremented with Vigor enabled (31 pts)
    assert(increment("Vigor"));
    assert(!decrement("Improved Poisons"));
    assert(!decrement("Lethality"));
    assert(!decrement("Murder"));
    assert(!decrement("Remorseless Attacks"));

    assert(decrement("Vigor"));
}

void TestAssassination::test_clearing_tree_after_filling() {
    assert(increment("Improved Eviscerate", 3));
    assert(increment("Malice", 5));
    assert(increment("Ruthlessness", 3));
    assert(increment("Murder", 2));
    assert(increment("Improved Slice and Dice", 3));
    assert(increment("Relentless Strikes", 1));
    assert(increment("Lethality", 5));
    assert(increment("Improved Poisons", 5));
    assert(increment("Vile Poisons", 5));
    assert(increment("Cold Blood"));
    assert(increment("Seal Fate", 5));
    assert(increment("Vigor"));

    assert(!decrement("Cold Blood"));

    clear_tree();
}

void TestAssassination::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_seal_fate();
    assert(tree_has_points(30));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_seal_fate();
    assert(tree_has_points(30));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_seal_fate();
    assert(tree_has_points(30));
}

void TestAssassination::spec_seal_fate() {
    assert(increment("Malice", 5));
    assert(increment("Ruthlessness", 3));
    assert(increment("Murder", 2));
    assert(increment("Improved Slice and Dice", 3));
    assert(increment("Relentless Strikes", 1));
    assert(increment("Lethality", 5));
    assert(increment("Improved Poisons", 5));
    assert(increment("Cold Blood", 1));
    assert(increment("Seal Fate", 5));
}

QString TestAssassination::get_position(const QString& name) const {
    if (name == "Improved Eviscerate")
        return "1LL";
    if (name == "Remorseless Attacks")
        return "1ML";
    if (name == "Malice")
        return "1MR";
    if (name == "Ruthlessness")
        return "2LL";
    if (name == "Murder")
        return "2ML";
    if (name == "Improved Slice and Dice")
        return "2RR";
    if (name == "Relentless Strikes")
        return "3LL";
    if (name == "Improved Expose Armor")
        return "3ML";
    if (name == "Lethality")
        return "3MR";
    if (name == "Vile Poisons")
        return "4ML";
    if (name == "Improved Poisons")
        return "4MR";
    if (name == "Cold Blood")
        return "5ML";
    if (name == "Improved Kidney Shot")
        return "5MR";
    if (name == "Seal Fate")
        return "6ML";
    if (name == "Vigor")
        return "7ML";

    assert(false);
    return "";
}
