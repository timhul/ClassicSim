#include "TestBuffWarrior.h"

#include <utility>

#include "Warrior.h"
#include "WarriorSpells.h"

TestBuffWarrior::TestBuffWarrior(EquipmentDb* equipment_db, QString buff_under_test) : TestBuff(equipment_db, std::move(buff_under_test)) {}

void TestBuffWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, equipment_db, sim_settings, raid_control);
    spells = static_cast<WarriorSpells*>(warrior->get_spells());
    warrior->set_clvl(60);
    warrior->gain_rage(100);
    pchar = warrior;
}

void TestBuffWarrior::tear_down() {
    delete warrior;
    tear_down_general();
}
