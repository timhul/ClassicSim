#include "TestUnbridledWrath.h"

#include "EnabledProcs.h"
#include "Fury.h"
#include "ProcInfo.h"
#include "Talent.h"
#include "UnbridledWrath.h"
#include "Warrior.h"
#include "WarriorSpells.h"

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
    return dynamic_cast<UnbridledWrath*>(spells->get_unbridled_wrath());
}

void TestUnbridledWrath::test_name_correct() {
    assert(spells->get_unbridled_wrath()->get_name() == "Unbridled Wrath");
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
    given_talent_rank(Fury(warrior), "Unbridled Wrath", 1);
}

void TestUnbridledWrath::given_2_of_5_unbridled_wrath() {
    given_talent_rank(Fury(warrior), "Unbridled Wrath", 2);
}

void TestUnbridledWrath::given_3_of_5_unbridled_wrath() {
    given_talent_rank(Fury(warrior), "Unbridled Wrath", 3);
}

void TestUnbridledWrath::given_4_of_5_unbridled_wrath() {
    given_talent_rank(Fury(warrior), "Unbridled Wrath", 4);
}

void TestUnbridledWrath::given_5_of_5_unbridled_wrath() {
    given_talent_rank(Fury(warrior), "Unbridled Wrath", 5);
}

void TestUnbridledWrath::test_proc_sources_are_valid() {
    assert(spells->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(spells->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::OffhandSwing));

    assert(!spells->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(!spells->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::MagicSpell));
    assert(!spells->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::RangedSpell));
    assert(!spells->get_unbridled_wrath()->procs_from_source(ProcInfo::Source::RangedAutoShot));
}
