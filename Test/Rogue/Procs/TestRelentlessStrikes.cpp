#include "TestRelentlessStrikes.h"

#include "Assassination.h"
#include "EnabledProcs.h"
#include "ProcInfo.h"
#include "RelentlessStrikes.h"
#include "Rogue.h"
#include "Talent.h"

TestRelentlessStrikes::TestRelentlessStrikes(EquipmentDb* equipment_db) :
    TestProcRogue(equipment_db, "Relentless Strikes")
{}

void TestRelentlessStrikes::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_proc_range();
    tear_down();

    set_up();
    test_proc_sources_are_valid();
    tear_down();
}

RelentlessStrikes* TestRelentlessStrikes::relentless_strikes() const {
    return rogue->get_relentless_strikes();
}

void TestRelentlessStrikes::test_name_correct() {
    assert(relentless_strikes()->get_name() == "Relentless Strikes");
}

void TestRelentlessStrikes::test_proc_range() {
    given_1_of_1_relentless_strikes();

    rogue->gain_combo_points(1);
    assert(rogue->get_combo_points() == 1);
    relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
    then_proc_range_is(relentless_strikes(), 2000);

    rogue->gain_combo_points(1);
    assert(rogue->get_combo_points() == 2);
    relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
    then_proc_range_is(relentless_strikes(), 4000);

    rogue->gain_combo_points(1);
    assert(rogue->get_combo_points() == 3);
    relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
    then_proc_range_is(relentless_strikes(), 6000);

    rogue->gain_combo_points(1);
    assert(rogue->get_combo_points() == 4);
    relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
    then_proc_range_is(relentless_strikes(), 8000);

    rogue->gain_combo_points(1);
    assert(rogue->get_combo_points() == 5);
    relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
    then_proc_range_is(relentless_strikes(), 10000);
}

void TestRelentlessStrikes::given_1_of_1_relentless_strikes() {
    Talent* talent = Assassination(rogue).get_relentless_strikes();

    assert(talent->increment_rank());

    delete talent;
}

void TestRelentlessStrikes::test_proc_sources_are_valid() {
    assert(relentless_strikes()->procs_from_source(ProcInfo::Source::Manual));

    assert(!relentless_strikes()->procs_from_source(ProcInfo::Source::MainhandSpell));
    assert(!relentless_strikes()->procs_from_source(ProcInfo::Source::MainhandSwing));
    assert(!relentless_strikes()->procs_from_source(ProcInfo::Source::OffhandSwing));
}
