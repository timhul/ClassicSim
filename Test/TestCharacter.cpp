
#include "TestCharacter.h"
#include "EquipmentDb.h"

TestCharacter::TestCharacter() :
    equipment_db(new EquipmentDb())
{}

TestCharacter::~TestCharacter() {
    delete equipment_db;
}

double TestCharacter::delta(double lhs, double rhs) {
    return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
}
