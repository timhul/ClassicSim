
#include "TestWarrior.h"

#include "Warrior.h"
#include "Orc.h"

#include "Engine.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "TestExecute.h"

void TestWarrior::test_all() {
    TestExecute().test_all();
}

void TestWarrior::test_char_initialization() {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Target* target = new Target(63);
    CombatRoll* combat = new CombatRoll(target);

    Race* race = new Orc();
    Warrior* warr = new Warrior(race, engine, equipment, combat);

    assert(warr->get_name() == "Warrior");
    assert(warr->get_race()->get_name() == "Orc");
    // TODO: Add more assertions

    delete race;
    delete warr;
    delete engine;
    delete equipment;
    delete combat;
    delete target;
}
