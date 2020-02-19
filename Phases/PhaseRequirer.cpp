#include "PhaseRequirer.h"

PhaseRequirer::PhaseRequirer(const Content::Phase phase) : phase(phase) {}

bool PhaseRequirer::valid_for_phase(const Content::Phase phase) {
    return static_cast<int>(this->phase) <= static_cast<int>(phase);
}
