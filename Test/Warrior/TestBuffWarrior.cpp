
#include "TestBuffWarrior.h"

#include "Warrior.h"

TestBuffWarrior::TestBuffWarrior(QString buff_under_test) :
    TestBuff(buff_under_test)
{}

void TestBuffWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, engine, equipment, combat, faction);
    warrior->set_clvl(60);
    warrior->gain_rage(100);
    pchar = warrior;
}

void TestBuffWarrior::tear_down() {
    tear_down_general();
    delete warrior;
}
