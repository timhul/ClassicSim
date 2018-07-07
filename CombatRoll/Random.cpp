
#include "Random.h"

Random::Random(const int min_range, const int max_range):
    min_range(min_range),
    modulo(max_range - min_range),
    xoroshiro(new xoroshiro128plus())
{}

Random::~Random() {
    delete xoroshiro;
}

void Random::set_gen_from_seed(const unsigned long seed) {
    xoroshiro->set_state((uint64_t)seed);
}

int Random::get_roll(void) {
    if (modulo == 0)
        return min_range;
    return (xoroshiro->next() % modulo) + min_range;
}
