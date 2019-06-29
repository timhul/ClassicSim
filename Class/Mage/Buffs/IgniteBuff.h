#pragma once

#include "SharedDebuff.h"

#include <QVector>

class Character;

class IgniteBuff: public SharedDebuff {
public:
    IgniteBuff(Character* pchar);

    void increase_ignite_size(const double ignite_damage, const int instance_id);
    int get_current_owner() const;
    int get_current_iteration() const;
    double get_tick_size() const;

private:
    int owner_instance_id {-1};
    int current_iteration {0};
    double current_tick {0.0};
    QVector<double> current_effects;

    void reset_effect() override;
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
