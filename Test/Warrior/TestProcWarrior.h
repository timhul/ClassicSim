#pragma once

#include "TestProc.h"

class Warrior;
class WarriorSpells;

class TestProcWarrior : public TestProc {
public:
    TestProcWarrior(EquipmentDb* equipment_db, QString proc_under_test);

protected:
    Warrior* warrior {nullptr};
    WarriorSpells* spells {nullptr};

    void set_up();
    void tear_down();
};
