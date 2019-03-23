#ifndef XOROSHIRO128PLUS_H
#define XOROSHIRO128PLUS_H

#include <stdint.h>

class xoroshiro128plus {
public:
    xoroshiro128plus();

    void set_state(uint64_t);
    uint64_t next();
    uint64_t state[2]{};
};

#endif // XOROSHIRO128PLUS_H
