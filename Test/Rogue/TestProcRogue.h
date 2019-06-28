#pragma once

#include "TestProc.h"
#include "Rogue.h"

class TestProcRogue: public TestProc {
public:
    TestProcRogue(EquipmentDb* equipment_db, QString proc_under_test);


protected:
    Rogue* rogue;

    void set_up();
    void tear_down();
};
