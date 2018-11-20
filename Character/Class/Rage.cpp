#include <cassert>

#include "Rage.h"

Rage::Rage()
{
    this->current = 0;
    this->max = 100;
}

void Rage::gain_resource(const unsigned rage) {
    current += rage;

    if (current > max)
        current = max;
}

void Rage::lose_resource(const unsigned rage) {
    assert(current >= rage);
    current -= rage;
}

void Rage::reset_resource() {
    current = 0;
}
