
#include "TestFury.h"
#include "Fury.h"
#include "Warrior.h"
#include "Orc.h"

TestFury::TestFury(EquipmentDb* equipment_db):
    equipment_db(equipment_db)
{}

void TestFury::set_up() {
    race = new Orc();
    warrior = new Warrior(race, equipment_db);
    fury = new Fury(warrior);
}

void TestFury::tear_down() {
    delete warrior;
    delete fury;
}

void TestFury::test_all() {
    set_up();
    test_fury_talents();
    tear_down();
}

void TestFury::test_fury_talents() {
    assert(!decrement("Cruelty"));

    assert(increment_talent_num_times("Cruelty", 5));
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

    assert(increment_talent_num_times("UW", 4));
    assert(increment_talent_num_times("Imp BS", 5));
    assert(increment_talent_num_times("Enrage", 5));
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

    assert(increment_talent_num_times("DW Spec", 5));
    assert(increment_talent_num_times("Flurry", 5));
    assert(increment_talent_num_times("Imp Execute", 2));
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

bool TestFury::increment(const QString& name) {
    return fury->increment_rank(get_position(name));
}

bool TestFury::decrement(const QString& name) {
    return fury->decrement_rank(get_position(name));
}

bool TestFury::increment_talent_num_times(const QString& name, int num_times) {
    QString spell = get_position(name);
    bool success = true;
    for (int i = 0; i < num_times; ++i) {
        if (!fury->increment_rank(spell))
            success = false;
    }

    return success;
}

QString TestFury::get_position(const QString& name) {
    if (name == "BV")
        return "1ML";
    else if (name == "Cruelty")
        return "1MR";
    else if (name == "Imp Demo")
        return "2ML";
    else if (name == "UW")
        return "2MR";
    else if (name == "Imp Cleave")
        return "3LL";
    else if (name == "Piercing Howl")
        return "3ML";
    else if (name == "Blood Craze")
        return "3MR";
    else if (name == "Imp BS")
        return "3RR";
    else if (name == "DW Spec")
        return "4LL";
    else if (name == "Imp Execute")
        return "4ML";
    else if (name == "Enrage")
        return "4MR";
    else if (name == "Imp Slam")
        return "5LL";
    else if (name == "Death Wish")
        return "5ML";
    else if (name == "Imp Intercept")
        return "5RR";
    else if (name == "Imp Zerker Rage")
        return "6LL";
    else if (name == "Flurry")
        return "6MR";
    else if (name == "BT")
        return "7ML";

    assert(false);
    return "";
}
