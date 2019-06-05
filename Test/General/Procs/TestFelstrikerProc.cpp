
#include "TestFelstrikerProc.h"
#include "FelstrikerBuff.h"
#include "EnabledBuffs.h"
#include "CharacterStats.h"
#include "Equipment.h"
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
    pchar = new Warrior(race, equipment_db, sim_settings, target, raid_control);
}

void TestFelstrikerProc::tear_down() {
    delete pchar;
    tear_down_general();
}

void TestFelstrikerProc::test_crit_applied_and_removed() {
    given_felstriker_equipped_in_mainhand();
    given_an_offhand_axe();
    int mh_wpn_skill = pchar->get_mh_wpn_skill();
    int oh_wpn_skill = pchar->get_oh_wpn_skill();

    assert(mh_wpn_skill != oh_wpn_skill);

    FelstrikerBuff* buff = dynamic_cast<FelstrikerBuff*>(pchar->get_enabled_buffs()->use_shared_buff("Felstriker"));
    buff->prepare_set_of_combat_iterations();

    assert(buff != nullptr);
    assert(buff->get_name() == "Felstriker");

    set_melee_auto_table_for_miss(mh_wpn_skill);
    set_melee_auto_table_for_miss(oh_wpn_skill);
    set_melee_special_table_for_miss(mh_wpn_skill);
    set_melee_special_table_for_miss(oh_wpn_skill);

    const unsigned crit_before_buff = pchar->get_stats()->get_mh_crit_chance();
    buff->apply_buff();

    assert_melee_auto_table_can_only_crit(mh_wpn_skill);
    assert_melee_auto_table_can_only_crit(oh_wpn_skill);
    assert_melee_special_table_can_only_crit(mh_wpn_skill);
    assert_melee_special_table_can_only_crit(oh_wpn_skill);

    then_next_event_is("BuffRemoval", "3.000", RUN_EVENT);

    assert(crit_before_buff == pchar->get_stats()->get_mh_crit_chance());
}

void TestFelstrikerProc::given_felstriker_equipped_in_mainhand() {
    pchar->get_equipment()->set_mainhand(12590);
    assert(pchar->get_equipment()->get_mainhand()->get_name() == "Felstriker");
}
