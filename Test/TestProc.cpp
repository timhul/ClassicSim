#include "TestProc.h"
#include "Proc.h"

#include <cassert>
#include <utility>
#include <QDebug>

TestProc::TestProc(EquipmentDb *equipment_db, QString proc_under_test) :
    TestSpell(equipment_db, std::move(proc_under_test))
{}

void TestProc::then_proc_range_is(Proc* proc, const unsigned proc_range) {
    if (proc->get_proc_range() != proc_range) {
        qDebug() << spell_under_test << "- Expected proc range" << proc_range << "but got" << proc->get_proc_range();
        assert(false);
    }
}
