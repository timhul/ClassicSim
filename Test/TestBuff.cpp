
#include "TestBuff.h"
#include "Buff.h"

void TestBuff::then_number_of_charges_is(Buff *buff, const int charges) {
    assert(buff->get_charges() == charges);
}
