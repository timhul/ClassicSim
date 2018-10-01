#ifndef TESTBUFFWARRIOR_H
#define TESTBUFFWARRIOR_H

#include "TestBuff.h"
#include "Warrior.h"

class TestBuffWarrior: public TestBuff {
public:
    TestBuffWarrior(QString buff_under_test);

    void set_up();
    void tear_down();

protected:
    Warrior* warrior{};
};

#endif // TESTBUFFWARRIOR_H
