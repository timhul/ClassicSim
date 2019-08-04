#include "Rage.h"

#include "Utils/Check.h"

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
    check((current >= rage), "Underflow decrease Rage::lose_resource()");
    current -= rage;
}

void Rage::reset_resource() {
    current = 0;
}
