#pragma once

class EquipmentDb;

class Test {
public:
    Test();
    ~Test();

    void test_all();

private:
    EquipmentDb* equipment_db;

    void test_character_creation();
    void test_equipment_creation();
    void test_queue();
    void test_combat_roll_creation();
};
