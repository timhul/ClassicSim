#include "TestUnbridledWrath.h"

#include "EnabledProcs.h"
#include "ProcInfo.h"
#include "UnbridledWrath.h"
#include "UnbridledWrathTalent.h"
#include "Warrior.h"

TestUnbridledWrath::TestUnbridledWrath(EquipmentDb* equipment_db) :
    TestProcWarrior(equipment_db, "Unbridled Wrath")
{}

void TestUnbridledWrath::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_proc_range_for_1_of_5_unbridled_wrath();
    tear_down();

    set_up();
    test_proc_range_for_2_of_5_unbridled_wrath();
    tear_down();

    set_up();
    test_proc_range_for_3_of_5_unbridled_wrath();
    tear_down();

    set_up();
    test_proc_range_for_4_of_5_unbridled_wrath();
    tear_down();

    set_up();
    test_proc_range_for_5_of_5_unbridled_wrath();
    tear_down();

    set_up();
    test_proc_sources_are_valid();
    tear_down();
}

UnbridledWrath* TestUnbridledWrath::unbridled_wrath() {
    return warrior->get_unbridled_wrath();
}

void TestUnbridledWrath::test_name_correct() {
    assert(warrior->get_unbridled_wrath()->get_name() == "Unbridled Wrath");
}

void TestUnbridledWrath::test_proc_range_for_1_of_5_unbridled_wrath() {
    given_1_of_5_unbridled_wrath();

    then_proc_range_is(unbridled_wrath(), 800);
}

void TestUnbridledWrath::test_proc_range_for_2_of_5_unbridled_wrath() {
    given_2_of_5_unbridled_wrath();

    then_proc_range_is(unbridled_wrath(), 1600);
}

void TestUnbridledWrath::test_proc_range_for_3_of_5_unbridled_wrath() {
    given_3_of_5_unbridled_wrath();

    then_proc_range_is(unbridled_wrath(), 2400);
}

void TestUnbridledWrath::test_proc_range_for_4_of_5_unbridled_wrath() {
    given_4_of_5_unbridled_wrath();

    then_proc_range_is(unbridled_wrath(), 3200);
}

void TestUnbridledWrath::test_proc_range_for_5_of_5_unbridled_wrath() {
    given_5_of_5_unbridled_wrath();

    then_proc_range_is(unbridled_wrath(), 4000);
}

void TestUnbridledWrath::given_1_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    assert(uw.increment_rank());
}

void TestUnbridledWrath::given_2_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    assert(uw.increment_rank());
    assert(uw.increment_rank());
}

void TestUnbridledWrath::given_3_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    assert(uw.increment_rank());
    assert(uw.increment_rank());
    assert(uw.increment_rank());
}

void TestUnbridledWrath::given_4_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    assert(uw.increment_rank());
    assert(uw.increment_rank());
    assert(uw.increment_rank());
    assert(uw.increment_rank());
}

void TestUnbridledWrath::given_5_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    assert(uw.increment_rank());
    assert(uw.increment_rank());
    assert(uw.increment_rank());
    assert(uw.increment_rank());
    assert(uw.increment_rank());
}

void TestUnbridledWrath::test_proc_sources_are_valid() {
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::OffhandSpell));
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::OffhandSwing));
}
