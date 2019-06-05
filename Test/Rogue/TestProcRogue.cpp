
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
    rogue = new Rogue(race, equipment_db, sim_settings, target, raid_control);
    pchar = rogue;
}

void TestProcRogue::tear_down() {
    delete rogue;
    tear_down_general();
}
