#include "IgniteBuff.h"

#include <algorithm>

IgniteBuff::IgniteBuff(Character* pchar) : SharedDebuff(pchar, "Ignite", "Assets/spell/Spell_fire_incinerate.png", Priority::Low, 4, 0) {}

void IgniteBuff::increase_ignite_size(const double ignite_damage, const int instance_id) {
    if (current_effects.size() == 5)
        return;

    if (current_effects.empty())
        owner_instance_id = instance_id;

    current_effects.append(ignite_damage);
    current_tick = static_cast<double>(std::accumulate(current_effects.cbegin(), current_effects.cend(), 0)) / 4;
}

int IgniteBuff::get_current_owner() const {
    return this->owner_instance_id;
}

int IgniteBuff::get_current_iteration() const {
    return this->current_iteration;
}

double IgniteBuff::get_tick_size() const {
    return this->current_tick;
}

void IgniteBuff::reset_effect() {
    owner_instance_id = -1;
    current_tick = 0.0;
    current_effects.clear();

    current_iteration = 0;
}

void IgniteBuff::buff_effect_when_applied() {
    ++current_iteration;
}

void IgniteBuff::buff_effect_when_removed() {
    owner_instance_id = -1;
    current_tick = 0.0;
    current_effects.clear();
}
