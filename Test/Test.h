#ifndef TEST_H
#define TEST_H

#include "Engine.h"


class EquipmentDb;


class Test {
public:
    Test();
    ~Test();

    void test_all();
protected:
private:
    EquipmentDb* equipment_db;

    void test_special_hit_table();
    void test_white_hit_table();
    void test_white_hit_table_update();
    void test_character_creation();
    void test_equipment_creation();
    void test_queue();
    void test_mechanics_glancing_rate();
    void test_mechanics_glancing_dmg_penalty();
    void test_mechanics_dw_white_miss();
    void test_mechanics_dodge();
    void test_combat_roll_creation();
    void test_combat_roll_melee_hit_result();
    void test_random();
};


#endif // TEST_H
