#pragma once

#include "TestBuffWarrior.h"

class SunderArmor;

class TestDefiance : public TestBuffWarrior {
public:
    TestDefiance(EquipmentDb* equipment_db);

    void test_all();

    void set_up();

private:
    void test_hit_threat();
    void test_defensive_stance_threat_modifier();
    void test_battle_stance_threat_modifier();

    bool increment(QString name, int num_times = 1);
    bool increment_defiance(int num_times = 1);
    SunderArmor* sunder_armor() const;
    void when_sunder_armor_is_performed();
};
