#include "TestSurvival.h"

#include "Hunter.h"
#include "Orc.h"

TestSurvival::TestSurvival(EquipmentDb* equipment_db):
    TestTalentTree(equipment_db, "RIGHT")
{}

void TestSurvival::set_up() {
    race = new Orc();
    pchar = new Hunter(race, equipment_db, nullptr);
}

void TestSurvival::tear_down() {
    delete pchar;
    delete race;
}

void TestSurvival::test_spending_talent_points() {
    assert(!decrement("Deflection"));

    assert(increment("Deflection", 5));
    // 5 points
    assert(!increment("Deflection"));
    assert(decrement("Deflection"));
    assert(increment("Deflection"));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment("Savage Strikes"));
    assert(!decrement("Deflection"));
    assert(increment("Monster Slaying"));
    assert(decrement("Deflection"));
    assert(!decrement("Deflection"));
    assert(!decrement("Monster Slaying"));

    assert(increment("Deflection"));
    assert(decrement("Monster Slaying"));
    assert(decrement("Savage Strikes"));

    // Make Counterattack available via raw points
    assert(increment("Improved Wing Clip", 5));
    assert(increment("Survivalist", 5));
    assert(increment("Surefooted", 3));
    assert(increment("Trap Mastery", 2));

    // Assert cannot spend points into Counterattack if 1/1 Deterrence is missing
    assert(!increment("Counterattack"));
    assert(increment("Deterrence"));
    assert(increment("Counterattack"));

    // Make Wyvern Sting available via raw points
    assert(increment("Monster Slaying", 3));
    assert(increment("Lightning Reflexes", 5));

    // Assert cannot spend points into Wyvern Sting if 3/3 Killer Instinct is missing
    assert(!increment("Wyvern Sting"));
    assert(increment("Killer Instinct"));
    assert(!increment("Wyvern Sting"));
    assert(increment("Killer Instinct"));
    assert(!increment("Wyvern Sting"));
    assert(increment("Killer Instinct"));
    assert(increment("Wyvern Sting"));
}

void TestSurvival::test_clearing_tree_after_filling() {
    spec_survival();

    clear_tree();

    assert(tree_has_points(0));
}

void TestSurvival::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_survival();
    assert(tree_has_points(48));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_survival();
    assert(tree_has_points(48));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_survival();
    assert(tree_has_points(48));
}

void TestSurvival::spec_survival() {
    assert(increment("Humanoid Slaying", 3));
    assert(increment("Monster Slaying", 3));
    assert(increment("Deflection", 5));
    assert(increment("Entrapment", 5));
    assert(increment("Savage Strikes", 2));
    assert(increment("Improved Wing Clip", 5));
    assert(increment("Clever Traps", 2));
    assert(increment("Survivalist", 5));
    assert(increment("Deterrence", 1));
    assert(increment("Trap Mastery", 2));
    assert(increment("Surefooted", 3));
    assert(increment("Improved Feign Death", 2));
    assert(increment("Killer Instinct", 3));
    assert(increment("Counterattack", 1));
    assert(increment("Lightning Reflexes", 5));
    assert(increment("Wyvern Sting", 1));
}

QString TestSurvival::get_position(const QString& name) const {
    if (name == "Monster Slaying")
        return "1LL";
    if (name == "Humanoid Slaying")
        return "1ML";
    if (name == "Deflection")
        return "1MR";
    if (name == "Entrapment")
        return "2LL";
    if (name == "Savage Strikes")
        return "2ML";
    if (name == "Improved Wing Clip")
        return "2MR";
    if (name == "Clever Traps")
        return "3LL";
    if (name == "Survivalist")
        return "3ML";
    if (name == "Deterrence")
        return "3MR";
    if (name == "Trap Mastery")
        return "4LL";
    if (name == "Surefooted")
        return "4ML";
    if (name == "Improved Feign Death")
        return "4RR";
    if (name == "Killer Instinct")
        return "5ML";
    if (name == "Counterattack")
        return "5MR";
    if (name == "Lightning Reflexes")
        return "6MR";
    if (name == "Wyvern Sting")
        return "7ML";

    return "";
}
