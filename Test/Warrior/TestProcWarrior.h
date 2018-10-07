#ifndef TESTPROCWARRIOR_H
#define TESTPROCWARRIOR_H

#include "TestProc.h"
#include "Warrior.h"

class TestProcWarrior: public TestProc {
public:
    TestProcWarrior(EquipmentDb* equipment_db, QString proc_under_test);


protected:
    Warrior* warrior{};

    void set_up();
    void tear_down();
};

#endif // TESTPROCWARRIOR_H
