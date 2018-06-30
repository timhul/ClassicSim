
#include "TestBuff.h"
#include "Buff.h"

TestBuff::TestBuff(QString buff_under_test) :
    TestSpell(buff_under_test)
{}

void TestBuff::then_number_of_charges_is(Buff *buff, const int charges) {
    assert(buff->get_charges() == charges);
}
