
#include "TestWarrior.h"

#include "Warrior.h"
#include "Orc.h"

#include "Engine.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "Faction.h"
#include "TestExecute.h"
#include "TestHeroicStrike.h"
#include "TestBloodthirst.h"
#include "TestMainhandAttackWarrior.h"
#include "TestOffhandAttackWarrior.h"
#include "TestWhirlwind.h"
#include "TestOverpower.h"
#include "TestFlurryWarrior.h"
#include "TestDeepWounds.h"
#include "TestBloodrage.h"

void TestWarrior::test_all() {
    TestExecute().test_all();
    TestHeroicStrike().test_all();
    TestBloodthirst().test_all();
    TestMainhandAttackWarrior().test_all();
    TestOffhandAttackWarrior().test_all();
    TestWhirlwind().test_all();
    TestOverpower().test_all();
    TestFlurryWarrior().test_all();
    TestDeepWounds().test_all();
    TestBloodrage().test_all();
}

void TestWarrior::test_char_initialization() {
    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Target* target = new Target(63);
    CombatRoll* combat = new CombatRoll(target);
    Faction* faction = new Faction();

    Race* race = new Orc();
    Warrior* warr = new Warrior(race, engine, equipment, combat, faction);

    assert(warr->get_name() == "Warrior");
    assert(warr->get_race()->get_name() == "Orc");
    // TODO: Add more assertions

    delete faction;
    delete race;
    delete warr;
    delete engine;
    delete equipment;
    delete combat;
    delete target;
}
