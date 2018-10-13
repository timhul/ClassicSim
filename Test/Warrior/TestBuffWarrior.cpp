
#include "TestBuffWarrior.h"

#include "Warrior.h"

#include <utility>

TestBuffWarrior::TestBuffWarrior(EquipmentDb* equipment_db, QString buff_under_test) :
    TestBuff(equipment_db, std::move(buff_under_test))
{}

void TestBuffWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, equipment_db, nullptr);
    warrior->set_clvl(60);
    warrior->gain_rage(100);
    pchar = warrior;
}

void TestBuffWarrior::tear_down() {
    tear_down_general();
    delete warrior;
}
