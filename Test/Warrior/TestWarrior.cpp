
#include "TestWarrior.h"

#include "Warrior.h"
#include "Orc.h"

#include "Engine.h"
#include "Equipment.h"
#include "EquipmentDb.h"
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
#include "TestUnbridledWrath.h"
#include "TestRecklessness.h"
#include "TestBerserkerStance.h"

TestWarrior::TestWarrior() :
    equipment_db(new EquipmentDb())
{}

TestWarrior::~TestWarrior() {
    delete equipment_db;
}

void TestWarrior::test_all() {
    TestExecute(equipment_db).test_all();
    TestHeroicStrike(equipment_db).test_all();
    TestBloodthirst(equipment_db).test_all();
    TestMainhandAttackWarrior(equipment_db).test_all();
    TestOffhandAttackWarrior(equipment_db).test_all();
    TestWhirlwind(equipment_db).test_all();
    TestOverpower(equipment_db).test_all();
    TestFlurryWarrior(equipment_db).test_all();
    TestDeepWounds(equipment_db).test_all();
    TestBloodrage(equipment_db).test_all();
    TestUnbridledWrath(equipment_db).test_all();
    TestRecklessness(equipment_db).test_all();
    TestBerserkerStance(equipment_db).test_all();
}

void TestWarrior::test_char_initialization() {
    Race* race = new Orc();
    auto* warr = new Warrior(race, equipment_db);

    assert(warr->get_name() == "Warrior");
    assert(warr->get_race()->get_name() == "Orc");
    // TODO: Add more assertions

    delete race;
    delete warr;
}
