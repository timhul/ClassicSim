#include "Random.h"

#include "Utils/Check.h"

Random::Random(const unsigned min_range, const unsigned max_range):
    min_range(min_range),
    modulo(max_range - min_range),
    xoroshiro(new xoroshiro128plus())
{}

Random::~Random() {
    delete xoroshiro;
}

void Random::set_new_range(const unsigned min_range, const unsigned max_range) {
    check((min_range <= max_range), "Min must be <= max");
    this->min_range = min_range;
    this->modulo = max_range - min_range;
}

void Random::set_gen_from_seed(const unsigned long long seed) {
    xoroshiro->set_state(seed);
}

unsigned Random::get_roll() {
    if (modulo == 0)
        return static_cast<unsigned>(min_range);
    return static_cast<unsigned>((xoroshiro->next() % modulo) + min_range);
}
