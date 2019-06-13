#include "TestRestorationShaman.h"

#include "Orc.h"
#include "RaidControl.h"
#include "Shaman.h"
#include "SimSettings.h"

TestRestorationShaman::TestRestorationShaman(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestRestorationShaman::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Shaman(race, equipment_db, sim_settings, raid_control);
}

void TestRestorationShaman::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestRestorationShaman::test_spending_talent_points() {
    assert(increment("Improved Healing Wave", 5));
    assert(increment("Tidal Focus", 5));
    assert(increment("Totemic Focus", 5));
    assert(increment("Healing Focus", 5));
    assert(increment("Tidal Mastery", 5));
    assert(increment("Purification", 5));

    // Assert cannot increment Mana Tide Totem without Restorative Totems
    assert(tree_has_points(30));

    assert(!increment("Mana Tide Totem"));
    assert(increment("Restorative Totems", 5));
    assert(increment("Mana Tide Totem"));
    assert(!decrement("Restorative Totems"));
}

void TestRestorationShaman::test_clearing_tree_after_filling() {
    spec_restoration();

    clear_tree();

    assert(tree_has_points(0));
}

void TestRestorationShaman::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));
}

void TestRestorationShaman::spec_restoration() {
    assert(increment("Improved Healing Wave", 5));
    assert(increment("Tidal Focus", 5));
    assert(increment("Improved Reincarnation", 2));
    assert(increment("Ancestral Healing", 3));
    assert(increment("Totemic Focus", 5));
    assert(increment("Nature's Guidance", 3));
    assert(increment("Healing Focus", 5));
    assert(increment("Totemic Mastery", 1));
    assert(increment("Healing Grace", 3));
    assert(increment("Restorative Totems", 5));
    assert(increment("Tidal Mastery", 5));
    assert(increment("Healing Way", 3));
    assert(increment("Nature's Swiftness", 1));
    assert(increment("Purification", 4));
    assert(increment("Mana Tide Totem", 1));
}

QString TestRestorationShaman::get_position(const QString& name) const {
    if (name == "Improved Healing Wave")
        return "1ML";
    if (name == "Tidal Focus")
        return "1MR";
    if (name == "Improved Reincarnation")
        return "2LL";
    if (name == "Ancestral Healing")
        return "2ML";
    if (name == "Totemic Focus")
        return "2MR";
    if (name == "Nature's Guidance")
        return "3LL";
    if (name == "Healing Focus")
        return "3ML";
    if (name == "Totemic Mastery")
        return "3MR";
    if (name == "Healing Grace")
        return "3RR";
    if (name == "Restorative Totems")
        return "4ML";
    if (name == "Tidal Mastery")
        return "4MR";
    if (name == "Healing Way")
        return "5LL";
    if (name == "Nature's Swiftness")
        return "5MR";
    if (name == "Purification")
        return "6MR";
    if (name == "Mana Tide Totem")
        return "7ML";

    return "";
}
