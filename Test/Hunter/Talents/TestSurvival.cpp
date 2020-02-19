#include "TestSurvival.h"

#include <cassert>

#include "Hunter.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestSurvival::TestSurvival(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "RIGHT") {}

void TestSurvival::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestSurvival::tear_down() {
    delete pchar;
    delete race;
    delete raid_control;
    delete sim_settings;
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
