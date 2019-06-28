#pragma once

#include "TestObject.h"

class TestAttackTables : TestObject {
public:
    TestAttackTables(EquipmentDb* equipment_db);

    void test_all() override;

private:
    void test_values_after_initialization() override;
    void test_white_hit_table();
    void test_white_hit_table_update();
    void test_special_hit_table();
    void test_magic_attack_table();
};
