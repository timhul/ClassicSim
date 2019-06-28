#pragma once

#include "TestProc.h"

class TestFelstrikerProc : public TestProc {
public:
    TestFelstrikerProc(EquipmentDb* equipment_db);

    void test_all();

private:
    void test_crit_applied_and_removed();

    void given_felstriker_equipped_in_mainhand();

    void set_up();
    void tear_down();
};
