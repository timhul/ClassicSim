#pragma once

#include "Rogue.h"
#include "TestProc.h"

class TestProcRogue : public TestProc {
public:
    TestProcRogue(EquipmentDb* equipment_db, QString proc_under_test);

protected:
    Rogue* rogue;

    void set_up();
    void tear_down();
};
