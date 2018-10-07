#ifndef TESTTWOHANDEDWEAPONSPECIALIZATION_H
#define TESTTWOHANDEDWEAPONSPECIALIZATION_H

#include "TestWarriorUtils.h"

class EquipmentDb;
class Race;
class TwoHandedWeaponSpecialization;
class Warrior;

class TestTwoHandedWeaponSpecialization : public TestWarriorUtils {
public:
    TestTwoHandedWeaponSpecialization(EquipmentDb* equipment_db);

    void test_all();

    void test_name_is_correct();
    void test_damage_modified_when_using_2handers();
    void test_damage_not_modified_when_not_using_2handers();

    void test_damage_added_per_rank();

private:
    EquipmentDb* equipment_db;
    Warrior* warrior;
    TwoHandedWeaponSpecialization* talent;
    Race* race;

    void set_up();
    void tear_down();

    void test_basic_properties();
};

#endif // TESTTWOHANDEDWEAPONSPECIALIZATION_H
