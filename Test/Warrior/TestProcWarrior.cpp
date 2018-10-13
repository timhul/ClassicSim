
#include "TestProcWarrior.h"

#include "Warrior.h"
#include "Proc.h"

#include <utility>

TestProcWarrior::TestProcWarrior(EquipmentDb *equipment_db, QString spell_under_test) :
    TestProc(equipment_db, std::move(spell_under_test))
{}

void TestProcWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, equipment_db, nullptr);
    pchar = warrior;
}

void TestProcWarrior::tear_down() {
    tear_down_general();
    delete warrior;
}
