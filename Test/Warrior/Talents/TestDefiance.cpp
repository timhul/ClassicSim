#include "TestDefiance.h"

#include <cassert>

#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "Engine.h"
#include "Equipment.h"
#include "Event.h"
#include "Queue.h"
#include "SunderArmor.h"
#include "Talent.h"
#include "TestTalentTree.h"
#include "WarriorSpells.h"

TestDefiance::TestDefiance(EquipmentDb* equipment_db) : TestBuffWarrior(equipment_db, "Defiance") {}

void TestDefiance::set_up() {
    TestBuffWarrior::set_up();

    increment("Anticipation", 5);
    increment("Toughness", 5);
}

void TestDefiance::test_all() {
    set_up();
    test_defensive_stance_threat_modifier();
    tear_down();

    set_up();
    test_battle_stance_threat_modifier();
    tear_down();
}

void TestDefiance::test_defensive_stance_threat_modifier() {
    warrior->switch_to_defensive_stance();
    auto threat = pchar->get_stats()->get_total_threat_mod();
    assert(threat == 1.3);
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(1.34, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(1.38, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(1.42, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(1.46, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(1.50, threat));
};

void TestDefiance::test_battle_stance_threat_modifier() {
    warrior->switch_to_battle_stance();
    auto threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(0.8, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(0.8, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(0.8, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(0.8, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(0.8, threat));
    increment_defiance();
    threat = pchar->get_stats()->get_total_threat_mod();
    assert(almost_equal(0.8, threat));
}

bool TestDefiance::increment(QString name, int num_times) {
    QString spell = pchar->get_talents()->get_talent_position("RIGHT", name);
    bool success = true;
    for (int i = 0; i < num_times; ++i)
        if (!pchar->get_talents()->increment_rank("RIGHT", spell))
            success = false;

    return success;

}

bool TestDefiance::increment_defiance(int num_times) {
    return increment("Defiance", num_times);
}
