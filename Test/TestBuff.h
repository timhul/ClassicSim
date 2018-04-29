#ifndef TESTBUFF_H
#define TESTBUFF_H

#include "TestSpell.h"

class Buff;

class TestBuff : public TestSpell {
public:

    void then_number_of_charges_is(Buff* buff, const int charges);
};

#endif // TESTBUFF_H
