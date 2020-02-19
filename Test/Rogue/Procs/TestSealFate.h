#pragma once

#include "TestProcRogue.h"

class SealFate;

class TestSealFate : public TestProcRogue {
public:
    TestSealFate(EquipmentDb* equipment_db);

    void test_all();

private:
    SealFate* seal_fate() const;

    void test_name_correct();
    void test_proc_range_1_of_5_seal_fate();
    void test_proc_range_2_of_5_seal_fate();
    void test_proc_range_3_of_5_seal_fate();
    void test_proc_range_4_of_5_seal_fate();
    void test_proc_range_5_of_5_seal_fate();
    void test_proc_sources_are_valid();

    void given_1_of_5_seal_fate();
    void given_2_of_5_seal_fate();
    void given_3_of_5_seal_fate();
    void given_4_of_5_seal_fate();
    void given_5_of_5_seal_fate();
};
