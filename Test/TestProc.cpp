
#include "TestProc.h"

#include <utility>

TestProc::TestProc(EquipmentDb *equipment_db, QString proc_under_test) :
    TestSpell(equipment_db, std::move(proc_under_test))
{}
