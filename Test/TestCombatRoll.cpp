#include "TestCombatRoll.h"

#include <cassert>
#include <QDebug>

#include "CombatRoll.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warrior.h"

TestCombatRoll::TestCombatRoll(EquipmentDb* equipment_db) :
    equipment_db(equipment_db)
{}

void TestCombatRoll::test_all() {
    qDebug() << "TestCombatRoll";
    test_glancing_penalties();
}

void TestCombatRoll::test_glancing_penalties() {
    auto race = new Orc();
    auto sim_settings = new SimSettings();
    auto raid_control = new RaidControl(sim_settings);
    auto pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
    auto roll = pchar->get_combat_roll();

    for (int i = 0; i < 1000; ++i) {
        const double glance_penalty = roll->get_glancing_blow_dmg_penalty(300);
        assert(glance_penalty > 0.54999 && glance_penalty < 0.75001);
    }

    for (int i = 0; i < 1000; ++i) {
        const double glance_penalty = roll->get_glancing_blow_dmg_penalty(305);
        assert(glance_penalty > 0.7999 && glance_penalty < 0.9001);
    }

    for (int i = 0; i < 1000; ++i) {
        const double glance_penalty = roll->get_glancing_blow_dmg_penalty(310);
        assert(glance_penalty > 0.90999 && glance_penalty < 0.99001);
    }

    for (int i = 0; i < 1000; ++i) {
        const double glance_penalty = roll->get_glancing_blow_dmg_penalty(315);
        assert(glance_penalty > 0.90999 && glance_penalty < 0.99001);
    }

    delete pchar;
    delete race;
    delete raid_control;
    delete sim_settings;
}
