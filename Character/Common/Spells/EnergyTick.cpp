#include "EnergyTick.h"

#include "Energy.h"
#include "Utils/Check.h"

EnergyTick::EnergyTick(Character* pchar, class Energy* energy)
    :
      Spell("Energy Tick", "no-icon", pchar, RestrictedByGcd::No, 0.0, ResourceType::Energy, 0),
      energy(energy)
{}

void EnergyTick::spell_effect() {
    check(false, "Not implemented");
}

void EnergyTick::perform_periodic() {
    energy->tick_energy();
}
