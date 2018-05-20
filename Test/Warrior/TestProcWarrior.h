#ifndef TESTPROCWARRIOR_H
#define TESTPROCWARRIOR_H

#include "TestProc.h"
#include "Warrior.h"

class TestProcWarrior: public TestProc {
public:
    void set_up();
    void tear_down();

protected:
    Warrior* warrior;
};

#endif // TESTPROCWARRIOR_H
