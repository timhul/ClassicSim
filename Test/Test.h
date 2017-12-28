#ifndef TEST_H
#define TEST_H

#include "Engine.h"


class Test {
public:
    void test_all();
protected:
private:
    void test_white_hit_table();
    void test_character_creation();
    void test_equipment_creation();
    void test_queue();
    void test_combat_roll_glancing();
    void test_combat_roll_white_miss();
    void test_combat_roll_dodge();
    void test_combat_roll_creation();
    void test_combat_roll_melee_hit_result();
    void test_random();
};


#endif // TEST_H
