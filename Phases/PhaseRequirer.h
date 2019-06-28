#pragma once

#include "ContentPhase.h"

class PhaseRequirer {
public:
    PhaseRequirer(const Content::Phase phase);

    bool valid_for_phase(const Content::Phase phase);

    QString get_phase_string() const;

    const Content::Phase phase;
};
