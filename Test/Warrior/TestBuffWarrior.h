#ifndef TESTBUFFWARRIOR_H
#define TESTBUFFWARRIOR_H

#include "TestBuff.h"
#include "Warrior.h"

class TestBuffWarrior: public TestBuff {
public:
    TestBuffWarrior(EquipmentDb *equipment_db, QString buff_under_test);

    void set_up();
    void tear_down();

protected:
    Warrior* warrior {nullptr};
    WarriorSpells* spells {nullptr};
};

#endif // TESTBUFFWARRIOR_H
