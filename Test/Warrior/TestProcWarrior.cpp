
#include "TestProcWarrior.h"

#include "Warrior.h"

TestProcWarrior::TestProcWarrior(QString spell_under_test) :
    TestProc(spell_under_test)
{}

void TestProcWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, engine, equipment, combat, faction);
    warrior->set_clvl(60);
    warrior->gain_rage(100);
    pchar = warrior;
}

void TestProcWarrior::tear_down() {
    tear_down_general();
    delete warrior;
}
