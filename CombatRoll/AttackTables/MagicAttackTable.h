#ifndef MAGICATTACKTABLE_H
#define MAGICATTACKTABLE_H

#include <math.h>

#include "MagicAttackResult.h"
#include "MagicSchools.h"

class Mechanics;
class Random;

class MagicAttackTable {
public:
    MagicAttackTable(Mechanics* mechanics, Random* random, const int clvl, const unsigned spell_hit, const int target_res);
    ~MagicAttackTable() = default;

    int get_hit_outcome(const unsigned roll, const unsigned crit_chance) const;
    int get_resist_outcome(const unsigned roll) const;
    void update_miss_chance(const int clvl, const unsigned spell_hit);
    void update_target_resistance(const int target_resistance);

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

#endif // MAGICATTACKTABLE_H
