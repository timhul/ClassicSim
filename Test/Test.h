#ifndef TEST_H
#define TEST_H

class EquipmentDb;

class Test {
public:
    Test();
    ~Test();

    void test_all();
protected:
private:
    EquipmentDb* equipment_db;

    void test_character_creation();
    void test_equipment_creation();
    void test_queue();
    void test_combat_roll_creation();
    void test_combat_roll_melee_hit_result();
    void test_random();
};

#endif // TEST_H
