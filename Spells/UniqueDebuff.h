#pragma once

#include "Buff.h"

class UniqueDebuff: public Buff {
public:
    UniqueDebuff(Character* pchar, QString name, QString icon, const int duration, const int base_charges);

    void enable_buff() override final;
    void disable_buff() override final;

    void prepare_set_of_combat_iterations() override final;

protected:

private:
    void apply_buff_to_target() override final;
    void remove_buff_from_target() override final;
};
