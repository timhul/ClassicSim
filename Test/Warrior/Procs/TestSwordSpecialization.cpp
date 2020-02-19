#include "TestSwordSpecialization.h"

#include <cassert>

#include "Arms.h"
#include "CharacterStats.h"
#include "EnabledProcs.h"
#include "Equipment.h"
#include "ProcInfo.h"
#include "SwordSpecialization.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Weapon.h"

TestSwordSpecialization::TestSwordSpecialization(EquipmentDb* equipment_db) : TestProcWarrior(equipment_db, "Sword Specalization") {}

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
    assert(spells->get_sword_spec()->get_name() == "Sword Specialization");
}

void TestSwordSpecialization::test_proc_range_for_1_of_5_sword_spec() {
    given_talent_rank(Arms(warrior), "Sword Specialization", 1);

    then_proc_range_is(sword_spec(), 100);
}

void TestSwordSpecialization::test_proc_range_for_2_of_5_sword_spec() {
    given_talent_rank(Arms(warrior), "Sword Specialization", 2);

    then_proc_range_is(sword_spec(), 200);
}

void TestSwordSpecialization::test_proc_range_for_3_of_5_sword_spec() {
    given_talent_rank(Arms(warrior), "Sword Specialization", 3);

    then_proc_range_is(sword_spec(), 300);
}

void TestSwordSpecialization::test_proc_range_for_4_of_5_sword_spec() {
    given_talent_rank(Arms(warrior), "Sword Specialization", 4);

    then_proc_range_is(sword_spec(), 400);
}

void TestSwordSpecialization::test_proc_range_for_5_of_5_sword_spec() {
    given_talent_rank(Arms(warrior), "Sword Specialization", 5);

    then_proc_range_is(sword_spec(), 500);
}

void TestSwordSpecialization::test_mh_proc_conditions_fulfilled_if_using_sword_in_mh() {
    given_1h_sword_equipped_in_mainhand(warrior);

    SwordSpecialization spec(pchar);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());

    given_no_offhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_1h_axe_equipped_in_offhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_1h_mace_equipped_in_offhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_fist_weapon_equipped_in_offhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_dagger_equipped_in_offhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::test_mh_proc_conditions_fulfilled_if_using_2h_sword() {
    given_2h_sword_equipped(warrior);

    SwordSpecialization spec(pchar);

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
    SwordSpecialization spec(pchar);

    given_2h_axe_equipped(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_2h_mace_equipped(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_polearm_equipped(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSpell);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_staff_equipped(warrior);

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
    given_1h_axe_equipped_in_mainhand(warrior);
    given_1h_mace_equipped_in_offhand(warrior);

    SwordSpecialization spec(pchar);

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
    given_1h_sword_equipped_in_offhand(warrior);

    SwordSpecialization spec(pchar);

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::OffhandSwing);
    assert(spec.proc_specific_conditions_fulfilled());

    given_no_mainhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_1h_axe_equipped_in_mainhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_1h_mace_equipped_in_mainhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_fist_weapon_equipped_in_mainhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    given_dagger_equipped_in_mainhand(warrior);

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());

    spec.set_current_proc_source(ProcInfo::Source::MainhandSwing);
    assert(!spec.proc_specific_conditions_fulfilled());
}

void TestSwordSpecialization::test_proc_sources_are_valid() {
    assert(spells->get_sword_spec()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(spells->get_sword_spec()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(spells->get_sword_spec()->procs_from_source(ProcInfo::Source::OffhandSwing));
}

Proc* TestSwordSpecialization::sword_spec() {
    return spells->get_sword_spec();
}
