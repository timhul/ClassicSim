#ifndef TESTSWORDSPECIALIZATION_H
#define TESTSWORDSPECIALIZATION_H

#include "TestProcWarrior.h"

class SwordSpecialization;

class TestSwordSpecialization: public TestProcWarrior {
public:
    TestSwordSpecialization(EquipmentDb *equipment_db);

    void test_all();

private:
    SwordSpecialization* sword_spec();

    void test_name_correct();
    void test_proc_range_for_1_of_5_sword_spec();
    void test_proc_range_for_2_of_5_sword_spec();
    void test_proc_range_for_3_of_5_sword_spec();
    void test_proc_range_for_4_of_5_sword_spec();
    void test_proc_range_for_5_of_5_sword_spec();
    void test_proc_sources_are_valid();

    void test_proc_conditions_not_fulfilled_if_not_using_sword_in_either_mh_or_oh();

    void test_mh_proc_conditions_fulfilled_if_using_sword_in_mh();
    void test_oh_proc_conditions_fulfilled_if_using_sword_in_oh();

    void test_mh_proc_conditions_fulfilled_if_using_2h_sword();
    void test_mh_proc_conditions_not_fulfilled_if_using_other_types_of_2h();

    void given_1_of_5_sword_spec();
    void given_2_of_5_sword_pec();
    void given_3_of_5_sword_spec();
    void given_4_of_5_sword_spec();
    void given_5_of_5_sword_spec();
};

#endif // TESTSWORDSPECIALIZATION_H
