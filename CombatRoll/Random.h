#ifndef RANDOM_H
#define RANDOM_H

#include "xoroshiro128plus.h"


class Random {
public:
    Random(const unsigned min_range, const unsigned max_range);
    ~Random();

    void set_gen_from_seed(const unsigned long long seed);
    unsigned get_roll(void);
protected:
private:
    uint64_t min_range;
    uint64_t modulo;
    xoroshiro128plus* xoroshiro;
};

#endif // RANDOM_H
