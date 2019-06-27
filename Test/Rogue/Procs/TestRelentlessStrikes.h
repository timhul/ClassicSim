#pragma once

#include "TestProcRogue.h"

class RelentlessStrikes;

class TestRelentlessStrikes: public TestProcRogue {
public:
    TestRelentlessStrikes(EquipmentDb *equipment_db);

    void test_all();

private:
    RelentlessStrikes* relentless_strikes() const;

    void test_name_correct();
    void test_proc_range();
    void test_proc_sources_are_valid();

    void given_1_of_1_relentless_strikes();
};
