
#include "TestArms.h"
#include "Arms.h"
#include "Warrior.h"
#include "Orc.h"

TestArms::TestArms(EquipmentDb* equipment_db):
    equipment_db(equipment_db)
{}

void TestArms::set_up() {
    race = new Orc();
    warrior = new Warrior(race, equipment_db, nullptr);
    arms = new Arms(warrior);
}

void TestArms::tear_down() {
    delete warrior;
    delete arms;
}

void TestArms::test_all() {
    set_up();
    test_clear_tree();
    tear_down();

    set_up();
    test_arms_talents();
    tear_down();
}

void TestArms::test_arms_talents() {
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
    assert(!increment("Improved Rend"));
    assert(increment("Deep Wounds"));
    assert(!increment("Improved Rend"));
    assert(increment("Deep Wounds"));
    assert(!increment("Improved Rend"));


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
    assert(arms->get_total_points() == 30);
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

void TestArms::test_clear_tree() {
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

    arms->clear_tree();
}

bool TestArms::increment(const QString& name) {
    return arms->increment_rank(get_position(name));
}

bool TestArms::decrement(const QString& name) {
    return arms->decrement_rank(get_position(name));
}

bool TestArms::increment_talent_num_times(const QString& name, int num_times) {
    QString spell = get_position(name);
    bool success = true;
    for (int i = 0; i < num_times; ++i) {
        if (!arms->increment_rank(spell))
            success = false;
    }

    return success;
}

QString TestArms::get_position(const QString& name) {
    if (name == "Improved Heroic Strike")
        return "1LL";
    else if (name == "Deflection")
        return "1ML";
    else if (name == "Improved Rend")
        return "1MR";
    else if (name == "Improved Charge")
        return "2LL";
    else if (name == "Tactical Mastery")
        return "2ML";
    else if (name == "Improved Thunder Clap")
        return "2RR";
    else if (name == "Improved Overpower")
        return "3LL";
    else if (name == "Anger Management")
        return "3ML";
    else if (name == "Deep Wounds")
        return "3MR";
    else if (name == "Two-Handed Weapon Specialization")
        return "4ML";
    else if (name == "Impale")
        return "4MR";
    else if (name == "Axe Specialization")
        return "5LL";
    else if (name == "Sweeping Strikes")
        return "5ML";
    else if (name == "Mace Specialization")
        return "5MR";
    else if (name == "Sword Specialization")
        return "5RR";
    else if (name == "Polearm Specialization")
        return "6LL";
    else if (name == "Improved Hamstring")
        return "6MR";
    else if (name == "Mortal Strike")
        return "7ML";

    assert(false);
    return "";
}
