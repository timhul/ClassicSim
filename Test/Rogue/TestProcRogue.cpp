
#include "TestProcRogue.h"

#include "Rogue.h"
#include "Proc.h"

#include <utility>

TestProcRogue::TestProcRogue(EquipmentDb *equipment_db, QString spell_under_test) :
    TestProc(equipment_db, std::move(spell_under_test)),
    rogue(nullptr)
{}

void TestProcRogue::set_up() {
    set_up_general();
    rogue = new Rogue(race, equipment_db, nullptr);
    pchar = rogue;
}

void TestProcRogue::tear_down() {
    tear_down_general();
    delete rogue;
}
