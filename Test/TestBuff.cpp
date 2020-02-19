#include "TestBuff.h"

#include <cassert>
#include <utility>

#include "Buff.h"

TestBuff::TestBuff(EquipmentDb* equipment_db, QString buff_under_test) : TestSpell(equipment_db, std::move(buff_under_test)) {}

void TestBuff::then_number_of_charges_is(Buff* buff, const int charges) {
    assert(buff->get_charges() == charges);
}
