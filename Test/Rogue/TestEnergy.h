#ifndef TESTENERGY_H
#define TESTENERGY_H

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
    void then_rogue_has_energy(const unsigned) const;

    Rogue* rogue;
};

#endif // TESTENERGY_H
