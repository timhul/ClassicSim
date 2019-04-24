#include "TestRetribution.h"

#include "Human.h"
#include "Paladin.h"

TestRetribution::TestRetribution(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestRetribution::set_up() {
    race = new Human();
    pchar = new Paladin(race, equipment_db, nullptr);
}

void TestRetribution::tear_down() {
    delete pchar;
    delete race;
}

void TestRetribution::test_spending_talent_points() {
    // Assert cannot spend points into Vengeance if 5/5 Conviction missing
    assert(increment("Improved Blessing of Might", 5));
    assert(increment("Benediction", 5));
    assert(increment("Deflection", 5));
    assert(increment("Conviction", 4));
    assert(increment("Improved Retribution Aura", 2));
    assert(increment("Two-Handed Weapon Specialization", 3));
    assert(increment("Sanctity Aura"));

    assert(tree_has_points(25));
    assert(!increment("Vengeance"));
    assert(increment("Conviction"));
    assert(increment("Vengeance"));
    assert(!decrement("Conviction"));
}

void TestRetribution::test_clearing_tree_after_filling() {
    spec_retribution();

    clear_tree();

    assert(tree_has_points(0));
}

void TestRetribution::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_retribution();
    assert(tree_has_points(45));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_retribution();
    assert(tree_has_points(45));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_retribution();
    assert(tree_has_points(45));
}

void TestRetribution::spec_retribution() {
    assert(increment("Improved Blessing of Might", 5));
    assert(increment("Benediction", 5));
    assert(increment("Improved Judgement", 2));
    assert(increment("Improved Seal of the Crusader", 3));
    assert(increment("Deflection", 5));
    assert(increment("Vindication", 3));
    assert(increment("Conviction", 5));
    assert(increment("Seal of Command", 1));
    assert(increment("Pursuit of Justice", 2));
    assert(increment("Eye of an Eye", 2));
    assert(increment("Improved Retribution Aura", 2));
    assert(increment("Two-Handed Weapon Specialization", 3));
    assert(increment("Sanctity Aura", 1));
    assert(increment("Vengeance", 5));
    assert(increment("Repentance", 1));
}

QString TestRetribution::get_position(const QString& name) const {
    if (name == "Improved Blessing of Might")
        return "1ML";
    if (name == "Benediction")
        return "1MR";
    if (name == "Improved Judgement")
        return "2LL";
    if (name == "Improved Seal of the Crusader")
        return "2ML";
    if (name == "Deflection")
        return "2MR";
    if (name == "Vindication")
        return "3LL";
    if (name == "Conviction")
        return "3ML";
    if (name == "Seal of Command")
        return "3MR";
    if (name == "Pursuit of Justice")
        return "3RR";
    if (name == "Eye of an Eye")
        return "4LL";
    if (name == "Improved Retribution Aura")
        return "4MR";
    if (name == "Two-Handed Weapon Specialization")
        return "5LL";
    if (name == "Sanctity Aura")
        return "5MR";
    if (name == "Vengeance")
        return "6ML";
    if (name == "Repentance")
        return "7ML";

    return "";
}
