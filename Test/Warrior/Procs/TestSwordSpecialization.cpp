
#include "TestSwordSpecialization.h"
#include "SwordSpecialization.h"
#include "SwordSpecializationTalent.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Weapon.h"
#include "ActiveProcs.h"
#include "ProcInfo.h"

TestSwordSpecialization::TestSwordSpecialization(EquipmentDb* equipment_db) :
    TestProcWarrior(equipment_db, "Sword Specalization")
{}

void TestSwordSpecialization::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_proc_range_for_1_of_5_sword_spec();
    tear_down();

    set_up();
    test_proc_range_for_2_of_5_sword_spec();
    tear_down();

    set_up();
    test_proc_range_for_3_of_5_sword_spec();
    tear_down();

    set_up();
    test_proc_range_for_4_of_5_sword_spec();
    tear_down();

    set_up();
    test_proc_range_for_5_of_5_sword_spec();
    tear_down();

    set_up();
    test_proc_sources_are_valid();
    tear_down();

    set_up();
    test_mh_proc_conditions_fulfilled_if_using_sword_in_mh();
    tear_down();

    set_up();
    test_proc_conditions_not_fulfilled_if_not_using_sword_in_either_mh_or_oh();
    tear_down();

    set_up();
    test_mh_proc_conditions_fulfilled_if_using_2h_sword();
    tear_down();

    set_up();
    test_mh_proc_conditions_not_fulfilled_if_using_other_types_of_2h();
    tear_down();

    set_up();
    test_oh_proc_conditions_fulfilled_if_using_sword_in_oh();
    tear_down();
}

void TestSwordSpecialization::test_name_correct() {
    assert(warrior->get_sword_spec()->get_name() == "Sword Specialization");
}

void TestSwordSpecialization::test_proc_range_for_1_of_5_sword_spec() {
    given_1_of_5_sword_spec();

    then_proc_range_is(100);
}

void TestSwordSpecialization::test_proc_range_for_2_of_5_sword_spec() {
    given_2_of_5_sword_pec();

    then_proc_range_is(200);
}

void TestSwordSpecialization::test_proc_range_for_3_of_5_sword_spec() {
    given_3_of_5_sword_spec();

    then_proc_range_is(300);
}

void TestSwordSpecialization::test_proc_range_for_4_of_5_sword_spec() {
    given_4_of_5_sword_spec();

    then_proc_range_is(400);
}

void TestSwordSpecialization::test_proc_range_for_5_of_5_sword_spec() {
    given_5_of_5_sword_spec();

    then_proc_range_is(500);
}

void TestSwordSpecialization::given_1_of_5_sword_spec() {
    SwordSpecializationTalent spec(warrior, nullptr);
    spec.apply_rank_effect();
}

void TestSwordSpecialization::given_2_of_5_sword_pec() {
    SwordSpecializationTalent spec(warrior, nullptr);
    spec.apply_rank_effect();
    spec.apply_rank_effect();
}

void TestSwordSpecialization::given_3_of_5_sword_spec() {
    SwordSpecializationTalent spec(warrior, nullptr);
    spec.apply_rank_effect();
    spec.apply_rank_effect();
    spec.apply_rank_effect();
}

void TestSwordSpecialization::given_4_of_5_sword_spec() {
    SwordSpecializationTalent spec(warrior, nullptr);
    spec.apply_rank_effect();
    spec.apply_rank_effect();
    spec.apply_rank_effect();
    spec.apply_rank_effect();
}

void TestSwordSpecialization::given_5_of_5_sword_spec() {
    SwordSpecializationTalent spec(warrior, nullptr);
    spec.apply_rank_effect();
    spec.apply_rank_effect();
    spec.apply_rank_effect();
    spec.apply_rank_effect();
    spec.apply_rank_effect();
}

void TestSwordSpecialization::test_mh_proc_conditions_fulfilled_if_using_sword_in_mh() {
    given_warrior_has_1h_sword_equipped_in_mainhand();
    given_warrior_does_not_have_sword_equipped_in_offhand();

    SwordSpecialization spec(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::test_mh_proc_conditions_fulfilled_if_using_2h_sword() {
    given_warrior_has_2h_sword_equipped_in_mainhand();

    SwordSpecialization spec(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::test_mh_proc_conditions_not_fulfilled_if_using_other_types_of_2h() {
    given_warrior_has_2h_that_is_not_sword_equipped_in_mainhand();

    SwordSpecialization spec(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::test_proc_conditions_not_fulfilled_if_not_using_sword_in_either_mh_or_oh() {
    given_warrior_does_not_have_sword_equipped_in_mainhand();
    given_warrior_does_not_have_sword_equipped_in_offhand();

    SwordSpecialization spec(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::test_oh_proc_conditions_fulfilled_if_using_sword_in_oh() {
    given_warrior_does_not_have_sword_equipped_in_mainhand();
    given_warrior_has_1h_sword_equipped_in_offhand();

    SwordSpecialization spec(pchar->get_engine(), pchar, pchar->get_combat_roll());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::given_warrior_has_1h_sword_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Skullforge Reaver");
    warrior->get_stats()->get_equipment()->clear_offhand();

    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestSwordSpecialization::given_warrior_has_2h_sword_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Ashkandi, Greatsword of the Brotherhood");
    warrior->get_stats()->get_equipment()->clear_offhand();

    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_SWORD);
}

void TestSwordSpecialization::given_warrior_has_2h_that_is_not_sword_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Arcanite Reaper");
    warrior->get_stats()->get_equipment()->clear_offhand();

    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_AXE);
}

void TestSwordSpecialization::given_warrior_does_not_have_sword_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Frostbite");

    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestSwordSpecialization::given_warrior_has_1h_sword_equipped_in_offhand() {
    warrior->get_stats()->get_equipment()->set_offhand("Skullforge Reaver");

    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestSwordSpecialization::given_warrior_does_not_have_sword_equipped_in_offhand() {
    warrior->get_stats()->get_equipment()->set_offhand("Frostbite");

    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestSwordSpecialization::test_proc_sources_are_valid() {
    assert(warrior->get_sword_spec()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(warrior->get_sword_spec()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(warrior->get_sword_spec()->procs_from_source(ProcInfo::Source::OffhandSpell));
    assert(warrior->get_sword_spec()->procs_from_source(ProcInfo::Source::OffhandSwing));
}

void TestSwordSpecialization::then_proc_range_is(const unsigned proc_range) {
    assert(warrior->get_sword_spec()->get_proc_range() == proc_range);
}
