#include <cassert>

#include "Character.h"
#include "Energy.h"
#include "EnergyTick.h"
#include "Engine.h"
#include "ResourceGain.h"

Energy::Energy(Character* pchar) :
    pchar(pchar),
    energy_per_tick(20)
{
    this->max = 100;
    this->current = max;
    this->energy_tick = new EnergyTick(pchar, this);
}

Energy::~Energy() {
    delete energy_tick;
}

void Energy::gain_resource(const unsigned energy) {
    current += energy;

    if (current > max)
        current = max;
}

void Energy::add_next_tick() {
    auto* event = new ResourceGain(pchar, energy_tick, pchar->get_engine()->get_current_priority() + 2.0);
    pchar->get_engine()->add_event(event);
}

void Energy::tick_energy() {
    if (current == max)
        return;

    gain_resource(energy_per_tick);

    add_next_tick();
}

void Energy::lose_resource(const unsigned energy) {
    if (current == max)
        add_next_tick();

    assert(current >= energy);
    current -= energy;
}

void Energy::increase_energy_per_tick() {
    energy_per_tick = 40;
}

void Energy::decrease_energy_per_tick() {
    energy_per_tick = 20;
}

void Energy::reset_resource() {
    current = max;
    energy_per_tick = 20;
}
