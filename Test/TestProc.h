#ifndef TESTPROC_H
#define TESTPROC_H

#include "TestSpell.h"

class EquipmentDb;
class Proc;

class TestProc : public TestSpell {
public:
    TestProc(EquipmentDb* equipment_db, QString proc_under_test);

private:
};

#endif // TESTPROC_H
