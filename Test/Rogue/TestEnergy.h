#pragma once

#include "TestSpell.h"

class Rogue;

class TestEnergy: public TestSpell {
public:
    TestEnergy(EquipmentDb* equipment_db);

    void test_all();

private:
    void set_up();
    void tear_down();

    void test_energy_ticks_up_after_use();
    void test_energy_tick_adds_player_action_event();
    void test_losing_energy_while_non_max_does_not_change_energy_tick_timer();
    void test_energy_tick_timer_is_pushed_forward_if_completed_before_losing_energy_again();
    void test_only_single_resource_gain_is_queued();
    void test_vigor_changes_max_energy();

    void then_rogue_has_energy(const unsigned) const;

    Rogue* rogue;
};
