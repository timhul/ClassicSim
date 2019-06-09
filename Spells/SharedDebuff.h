#pragma once

#include "Buff.h"

class SharedDebuff: public Buff {
public:
    SharedDebuff(RaidControl* raid_control, QString name, QString icon, const int duration, const int base_charges);

    void enable_buff() override final;
    void disable_buff() override final;
    void apply_buff_to(Character* any_pchar);
    void remove_buff_from(Character* any_pchar);

    void prepare_set_of_combat_iterations() override final;

private:
    void apply_buff_to_target() override final;
    void remove_buff_from_target() override final;
};
