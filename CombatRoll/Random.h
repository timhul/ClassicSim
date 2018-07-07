#ifndef RANDOM_H
#define RANDOM_H

#include "xoroshiro128plus.h"


class Random {
public:
    Random(const int min_range, const int max_range);
    ~Random();

    void set_gen_from_seed(const unsigned long seed);
    int get_roll(void);
protected:
private:
    uint64_t min_range;
    uint64_t modulo;
    xoroshiro128plus* xoroshiro;
};

#endif // RANDOM_H
