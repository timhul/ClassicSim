
#include "TestProc.h"
#include "Proc.h"

#include <utility>

TestProc::TestProc(EquipmentDb *equipment_db, QString proc_under_test) :
    TestSpell(equipment_db, std::move(proc_under_test))
{}

void TestProc::then_proc_range_is(Proc* proc, const unsigned proc_range) {
    assert(proc->get_proc_range() == proc_range);
}
