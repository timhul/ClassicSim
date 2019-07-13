#include "RangedWhiteHitTable.h"

#include <cmath>

#include "Random.h"
#include "Utils/Check.h"

RangedWhiteHitTable::RangedWhiteHitTable(Random *random,
                                         const unsigned wpn_skill,
                                         const unsigned miss,
                                         const double block) :
    wpn_skill(wpn_skill),
    random(random),
    miss_range(miss)
{
    update_block_chance(block);
}

int RangedWhiteHitTable::get_outcome(const unsigned roll,
                                     const unsigned crit_chance,
                                     const bool include_block,
                                     const bool include_miss) {
    check((roll < 10000), "Roll outside range");

    unsigned range = 0;

    if (include_miss && roll < this->miss_range)
        return PhysicalAttackResult::MISS;
    range += include_miss ? miss_range : 0;

    if (include_block && roll < (range + this->block_range)) {
        if (random->get_roll() < range + crit_chance)
            return PhysicalAttackResult::BLOCK_CRITICAL;
        return PhysicalAttackResult::BLOCK;
    }
    range += include_block ? block_range : 0;

    if (random->get_roll() < range + crit_chance)
        return PhysicalAttackResult::CRITICAL;

    return PhysicalAttackResult::HIT;
}

void RangedWhiteHitTable::update_miss_chance(const unsigned miss) {
    this->miss_range = miss;
}

void RangedWhiteHitTable::update_block_chance(const double block) {
    this->block_range = static_cast<unsigned>(round(block * 10000));
}
