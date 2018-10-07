
#include "TestCharacter.h"
#include "EquipmentDb.h"

TestCharacter::TestCharacter() :
    equipment_db(new EquipmentDb())
{}

TestCharacter::~TestCharacter() {
    delete equipment_db;
}
