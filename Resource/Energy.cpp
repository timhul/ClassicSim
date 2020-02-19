#include "Energy.h"

Energy::Energy(Character* pchar) : RegeneratingResource(pchar), energy_per_tick(20), max_energy_bonus(0) {
    reset_resource();
}

unsigned Energy::get_max_resource() const {
    return 100 + max_energy_bonus;
}

unsigned Energy::get_resource_per_tick() {
    return energy_per_tick;
}

ResourceType Energy::get_resource_type() const {
    return ResourceType::Energy;
}

double Energy::get_tick_rate() const {
    return 2.0;
}

void Energy::reset_effect() {
    energy_per_tick = 20;
}

void Energy::lose_resource_effect() {}

void Energy::increase_energy_per_tick() {
    energy_per_tick = 40;
}

void Energy::decrease_energy_per_tick() {
    energy_per_tick = 20;
}
