#include "TestSealFate.h"

#include "EnabledProcs.h"
#include "ProcInfo.h"
#include "Rogue.h"
#include "SealFate.h"
#include "SealFateTalent.h"

TestSealFate::TestSealFate(EquipmentDb* equipment_db) :
    TestProcRogue(equipment_db, "Seal Fate")
{}

void TestSealFate::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_proc_range_1_of_5_seal_fate();
    tear_down();

    set_up();
    test_proc_range_2_of_5_seal_fate();
    tear_down();

    set_up();
    test_proc_range_3_of_5_seal_fate();
    tear_down();

    set_up();
    test_proc_range_4_of_5_seal_fate();
    tear_down();

    set_up();
    test_proc_range_5_of_5_seal_fate();
    tear_down();

    set_up();
    test_proc_sources_are_valid();
    tear_down();
}

SealFate* TestSealFate::seal_fate() {
    return rogue->get_seal_fate();
}

void TestSealFate::test_name_correct() {
    assert(seal_fate()->get_name() == "Seal Fate");
}

void TestSealFate::test_proc_range_1_of_5_seal_fate() {
    given_1_of_5_seal_fate();

    then_proc_range_is(seal_fate(), 2000);
}

void TestSealFate::test_proc_range_2_of_5_seal_fate() {
    given_2_of_5_seal_fate();

    then_proc_range_is(seal_fate(), 4000);
}

void TestSealFate::test_proc_range_3_of_5_seal_fate() {
    given_3_of_5_seal_fate();

    then_proc_range_is(seal_fate(), 6000);
}

void TestSealFate::test_proc_range_4_of_5_seal_fate() {
    given_4_of_5_seal_fate();

    then_proc_range_is(seal_fate(), 8000);
}

void TestSealFate::test_proc_range_5_of_5_seal_fate() {
    given_5_of_5_seal_fate();

    then_proc_range_is(seal_fate(), 10000);
}

void TestSealFate::given_1_of_5_seal_fate() {
    SealFateTalent relentless_strikes_talent(rogue, nullptr);
    assert(relentless_strikes_talent.increment_rank());
}

void TestSealFate::given_2_of_5_seal_fate() {
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
}

void TestSealFate::given_3_of_5_seal_fate() {
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
}

void TestSealFate::given_4_of_5_seal_fate() {
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
}

void TestSealFate::given_5_of_5_seal_fate() {
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
    given_1_of_5_seal_fate();
}

void TestSealFate::test_proc_sources_are_valid() {
    assert(seal_fate()->procs_from_source(ProcInfo::Source::Manual));

    assert(!seal_fate()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(!seal_fate()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(!seal_fate()->procs_from_source(ProcInfo::Source::OffhandSpell));
    assert(!seal_fate()->procs_from_source(ProcInfo::Source::OffhandSwing));
}
