
#include "Random.h"

Random::Random(const unsigned min_range, const unsigned max_range):
    min_range(min_range),
    modulo(max_range - min_range),
    xoroshiro(new xoroshiro128plus())
{}

Random::~Random() {
    delete xoroshiro;
}

void Random::set_gen_from_seed(const unsigned long long seed) {
    xoroshiro->set_state(seed);
}

unsigned Random::get_roll(void) {
    if (modulo == 0)
        return static_cast<unsigned>(min_range);
    return static_cast<unsigned>((xoroshiro->next() % modulo) + min_range);
}
