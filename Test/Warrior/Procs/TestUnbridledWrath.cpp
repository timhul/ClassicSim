
#include "TestUnbridledWrath.h"
#include "Warrior.h"
#include "Procs.h"
#include "UnbridledWrath.h"
#include "UnbridledWrathTalent.h"
#include "ProcInfo.h"

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

void TestUnbridledWrath::test_name_correct() {
    assert(warrior->get_unbridled_wrath()->get_name() == "Unbridled Wrath");
}

void TestUnbridledWrath::test_proc_range_for_1_of_5_unbridled_wrath() {
    given_1_of_5_unbridled_wrath();

    then_proc_range_is(800);
}

void TestUnbridledWrath::test_proc_range_for_2_of_5_unbridled_wrath() {
    given_2_of_5_unbridled_wrath();

    then_proc_range_is(1600);
}

void TestUnbridledWrath::test_proc_range_for_3_of_5_unbridled_wrath() {
    given_3_of_5_unbridled_wrath();

    then_proc_range_is(2400);
}

void TestUnbridledWrath::test_proc_range_for_4_of_5_unbridled_wrath() {
    given_4_of_5_unbridled_wrath();

    then_proc_range_is(3200);
}

void TestUnbridledWrath::test_proc_range_for_5_of_5_unbridled_wrath() {
    given_5_of_5_unbridled_wrath();

    then_proc_range_is(4000);
}

void TestUnbridledWrath::given_1_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    uw.apply_rank_effect();
}

void TestUnbridledWrath::given_2_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    uw.apply_rank_effect();
    uw.apply_rank_effect();
}

void TestUnbridledWrath::given_3_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    uw.apply_rank_effect();
    uw.apply_rank_effect();
    uw.apply_rank_effect();
}

void TestUnbridledWrath::given_4_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    uw.apply_rank_effect();
    uw.apply_rank_effect();
    uw.apply_rank_effect();
    uw.apply_rank_effect();
}

void TestUnbridledWrath::given_5_of_5_unbridled_wrath() {
    UnbridledWrathTalent uw(warrior, nullptr);
    uw.apply_rank_effect();
    uw.apply_rank_effect();
    uw.apply_rank_effect();
    uw.apply_rank_effect();
    uw.apply_rank_effect();
}

void TestUnbridledWrath::test_proc_sources_are_valid() {
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::OffhandSpell));
    assert(warrior->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::OffhandSwing));
}

void TestUnbridledWrath::then_proc_range_is(const int proc_range) {
    assert(warrior->get_unbridled_wrath()->get_proc_range() == proc_range);
}
