#ifndef MECHANICS_H
#define MECHANICS_H

#include <algorithm>
#include "math.h"

class Target;

class Mechanics {
public:
    Mechanics(Target*);

    float get_yellow_miss_chance(const int) const;
    float get_1h_white_miss_chance(const int) const;
    float get_2h_white_miss_chance(const int) const;
    float get_dw_white_miss_chance(const int) const;

    float get_glancing_blow_chance(const int) const;
    float get_dodge_chance(const int) const;
    float get_parry_chance(const int) const;
    float get_block_chance(void) const;

    float get_glancing_blow_dmg_penalty(const int) const;

    float get_reduction_from_armor(const int, const int) const;

    void set_tlvl(const int);
protected:
private:
    Target* target;
};

#endif // MECHANICS_H
