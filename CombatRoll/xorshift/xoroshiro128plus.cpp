/*  Written in 2016-2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

Minor modifications made by Tim Hultman (tim.hultman@gmail.com):
    - Comparisons between signed and unsigned expressions (to fix compilation warnings)
    - Wrapped into class
    - Automatic seed based on OS tick count
    - Code style changes

See http://vigna.di.unimi.it/xorshift/ for an explanation of PRNGs developed by Vigna, et al.
See http://vigna.di.unimi.it/xorshift/xoroshiro128plus.c for the original C code.

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <cstdint>
#include "xoroshiro128plus.h"

#if defined(_MSC_VER)
    /* Microsoft C/C++-compatible compiler */
    #include <intrin.h>
    #define _rdtsc() __rdtsc()
#elif defined(__GNUC__)
    /* GCC-compatible compiler */
    #include <x86intrin.h>
#endif

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

xoroshiro128plus::xoroshiro128plus() {
    set_state(_rdtsc());
}

void xoroshiro128plus::set_state(uint64_t state) {
    this->state[0] = state;
    this->state[1] = _rdtsc();
    for (int i = 0; i < 100; ++i)
        this->next();
}

uint64_t xoroshiro128plus::next() {
    const uint64_t s0 = state[0];
    uint64_t s1 = state[1];
    const uint64_t result = s0 + s1;

    s1 ^= s0;
    state[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16);
    state[1] = rotl(s1, 37);

    return result;
}
