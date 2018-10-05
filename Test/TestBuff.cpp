
#include "TestBuff.h"
#include "Buff.h"

#include <utility>

TestBuff::TestBuff(EquipmentDb *equipment_db, QString buff_under_test) :
    TestSpell(equipment_db, std::move(buff_under_test))
{}

void TestBuff::then_number_of_charges_is(Buff *buff, const int charges) {
    assert(buff->get_charges() == charges);
}
