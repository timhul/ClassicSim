#include "TestCombatRoll.h"

#include <QDebug>

#include "CombatRoll.h"
#include "Target.h"
#include "Orc.h"
#include "Warrior.h"

TestCombatRoll::TestCombatRoll(EquipmentDb* equipment_db) :
    equipment_db(equipment_db)
{}

void TestCombatRoll::test_all() {
    qDebug() << "TestCombatRoll";
    test_glancing_penalties();
}

void TestCombatRoll::test_glancing_penalties() {
    auto* race = new Orc();
    auto* pchar = new Warrior(race, equipment_db, nullptr);
    auto* roll = pchar->get_combat_roll();

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
}
