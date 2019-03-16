#include "Energy.h"
#include "EnergyTick.h"

EnergyTick::EnergyTick(Character* pchar, class Energy* energy)
    :
      Spell("Energy Tick", "no-icon", pchar, RestrictedByGcd::No, 0.0, ResourceType::Energy, 0),
      energy(energy)
{}

void EnergyTick::spell_effect() {
    assert(false);
}

void EnergyTick::perform_periodic() {
    energy->tick_energy();
}
