#pragma once

#include <math.h>

#include "MagicAttackResult.h"
#include "MagicSchools.h"

class Mechanics;
class Random;

class MagicAttackTable {
public:
    MagicAttackTable(Mechanics* mechanics, Random* random, const unsigned clvl, const unsigned spell_hit, const unsigned target_res);
    ~MagicAttackTable() = default;

    int get_hit_outcome(const unsigned roll, const unsigned crit_chance) const;
    int get_resist_outcome(const unsigned roll) const;
    void update_miss_chance(const unsigned clvl, const unsigned spell_hit);
    void update_target_resistance(const unsigned target_resistance);

private:
    friend class TestSpell;

    Mechanics* mechanics;
    Random* random;

    unsigned miss_range;

    unsigned full_resist;
    unsigned partial_75;
    unsigned partial_50;
    unsigned partial_25;
};
