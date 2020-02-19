#pragma once

#include <stdint.h>

class xoroshiro128plus {
public:
    xoroshiro128plus();

    void set_state(uint64_t);
    uint64_t next();
    uint64_t state[2] {};
};
