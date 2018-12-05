#ifndef TESTPROCROGUE_H
#define TESTPROCROGUE_H

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

#endif // TESTPROCROGUE_H
