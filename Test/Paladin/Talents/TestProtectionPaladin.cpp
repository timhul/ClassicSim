#include "TestProtectionPaladin.h"

#include "Human.h"
#include "Paladin.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestProtectionPaladin::TestProtectionPaladin(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "MID")
{}

void TestProtectionPaladin::set_up() {
    race = new Human();
    raid_control = new RaidControl(sim_settings);
    pchar = new Paladin(race, equipment_db, sim_settings, raid_control);
}

void TestProtectionPaladin::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestProtectionPaladin::test_spending_talent_points() {
    assert(!decrement("Redoubt"));

    assert(increment("Redoubt", 5));
    // 5 points
    assert(!increment("Redoubt"));
    assert(decrement("Redoubt"));
    assert(increment("Redoubt"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Precision"));
    assert(!decrement("Redoubt"));
    assert(increment("Improved Devotion Aura"));
    assert(decrement("Redoubt"));
    assert(!decrement("Redoubt"));
    assert(!decrement("Improved Devotion Aura"));

    assert(increment("Redoubt"));
    assert(decrement("Improved Devotion Aura"));
    assert(increment("Precision", 2));
    assert(increment("Guardian's Favor", 2));

    // Assert cannot spend points into Shield Specialization if Redoubt is missing.
    assert(increment("Improved Devotion Aura"));
    assert(decrement("Redoubt"));
    assert(!increment("Shield Specialization"));
    assert(increment("Redoubt"));
    assert(increment("Shield Specialization"));
    assert(!decrement("Redoubt"));
}

void TestProtectionPaladin::test_clearing_tree_after_filling() {
    spec_protection();

    clear_tree();

    assert(tree_has_points(0));
}

void TestProtectionPaladin::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_protection();
    assert(tree_has_points(50));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_protection();
    assert(tree_has_points(50));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_protection();
    assert(tree_has_points(50));
}

void TestProtectionPaladin::spec_protection() {
    assert(increment("Improved Devotion Aura", 5));
    assert(increment("Redoubt", 5));
    assert(increment("Precision", 3));
    assert(increment("Guardian's Favor", 2));
    assert(increment("Toughness", 5));
    assert(increment("Blessing of Kings", 1));
    assert(increment("Improved Righteous Fury", 3));
    assert(increment("Shield Specialization", 3));
    assert(increment("Anticipation", 5));
    assert(increment("Improved Hammer of Justice", 3));
    assert(increment("Improved Concentration Aura", 3));
    assert(increment("Blessing of Sanctuary", 1));
    assert(increment("Reckoning", 5));
    assert(increment("One-Handed Weapon Specialization", 5));
    assert(increment("Holy Shield", 1));
}

QString TestProtectionPaladin::get_position(const QString& name) const {
    if (name == "Improved Devotion Aura")
        return "1ML";
    if (name == "Redoubt")
        return "1MR";
    if (name == "Precision")
        return "2LL";
    if (name == "Guardian's Favor")
        return "2ML";
    if (name == "Toughness")
        return "2RR";
    if (name == "Blessing of Kings")
        return "3LL";
    if (name == "Improved Righteous Fury")
        return "3ML";
    if (name == "Shield Specialization")
        return "3MR";
    if (name == "Anticipation")
        return "3RR";
    if (name == "Improved Hammer of Justice")
        return "4ML";
    if (name == "Improved Concentration Aura")
        return "4MR";
    if (name == "Blessing of Sanctuary")
        return "5ML";
    if (name == "Reckoning")
        return "5MR";
    if (name == "One-Handed Weapon Specialization")
        return "6MR";
    if (name == "Holy Shield")
        return "7ML";

    return "";
}
