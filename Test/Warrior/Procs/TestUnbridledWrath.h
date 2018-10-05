#ifndef TESTUNBRIDLEDWRATH_H
#define TESTUNBRIDLEDWRATH_H

#include "TestProcWarrior.h"

class TestUnbridledWrath: public TestProcWarrior {
public:
    TestUnbridledWrath(EquipmentDb *equipment_db);

    void test_all();

    void test_name_correct();
    void test_proc_range_for_1_of_5_unbridled_wrath();
    void test_proc_range_for_2_of_5_unbridled_wrath();
    void test_proc_range_for_3_of_5_unbridled_wrath();
    void test_proc_range_for_4_of_5_unbridled_wrath();
    void test_proc_range_for_5_of_5_unbridled_wrath();
    void test_proc_sources_are_valid();

    void given_1_of_5_unbridled_wrath();
    void given_2_of_5_unbridled_wrath();
    void given_3_of_5_unbridled_wrath();
    void given_4_of_5_unbridled_wrath();
    void given_5_of_5_unbridled_wrath();

    void then_proc_range_is(const unsigned);

private:
};

#endif // TESTUNBRIDLEDWRATH_H
