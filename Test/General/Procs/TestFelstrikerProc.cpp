#include "TestFelstrikerProc.h"

#include <cassert>

#include "CharacterStats.h"
#include "EnabledBuffs.h"
#include "Equipment.h"
#include "Event.h"
#include "FelstrikerBuff.h"
#include "Warrior.h"
#include "Weapon.h"

TestFelstrikerProc::TestFelstrikerProc(EquipmentDb* equipment_db) :
    TestProc(equipment_db, "Felstriker")
{}

void TestFelstrikerProc::test_all() {
    set_up();
    test_crit_applied_and_removed();
    tear_down();
}

void TestFelstrikerProc::set_up() {
    set_up_general();
    pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
}

void TestFelstrikerProc::tear_down() {
    delete pchar;
    tear_down_general();
}

void TestFelstrikerProc::test_crit_applied_and_removed() {
    given_felstriker_equipped_in_mainhand();
    given_an_offhand_axe();
    unsigned mh_wpn_skill = pchar->get_mh_wpn_skill();
    unsigned oh_wpn_skill = pchar->get_oh_wpn_skill();

    assert(mh_wpn_skill != oh_wpn_skill);

    auto* buff = dynamic_cast<FelstrikerBuff*>(pchar->get_enabled_buffs()->use_shared_buff("Felstriker"));
    buff->prepare_set_of_combat_iterations();

    assert(buff != nullptr);
    assert(buff->get_name() == "Felstriker");

    const unsigned crit_before_buff = pchar->get_stats()->get_mh_crit_chance();
    const unsigned hit_before_buff = pchar->get_stats()->get_melee_hit_chance();
    buff->apply_buff();

    const unsigned aura_crit_suppression = 180;
    assert(crit_before_buff + 10000 - aura_crit_suppression == pchar->get_stats()->get_mh_crit_chance());
    assert(hit_before_buff + 10000 == pchar->get_stats()->get_melee_hit_chance());

    then_next_event_is(EventType::BuffRemoval, "3.000", RUN_EVENT);

    assert(crit_before_buff == pchar->get_stats()->get_mh_crit_chance());
    assert(hit_before_buff == pchar->get_stats()->get_melee_hit_chance());
}

void TestFelstrikerProc::given_felstriker_equipped_in_mainhand() {
    pchar->get_equipment()->set_mainhand(12590);
    assert(pchar->get_equipment()->get_mainhand()->name == "Felstriker");
}
