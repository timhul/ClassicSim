#include "RangedWhiteHitTable.h"

#include <cmath>

#include "Random.h"
#include "Utils/Check.h"

RangedWhiteHitTable::RangedWhiteHitTable(Random *random,
                                         const int wpn_skill,
                                         const unsigned miss,
                                         const double dodge,
                                         const double block) :
    random(random),
    wpn_skill(wpn_skill),
    miss_range(miss)
{
    update_dodge_chance(dodge);
    update_block_chance(block);
}

int RangedWhiteHitTable::get_wpn_skill() const {
    return wpn_skill;
}

int RangedWhiteHitTable::get_outcome(const unsigned roll,
                                     const unsigned crit_chance,
                                     const bool include_dodge,
                                     const bool include_block,
                                     const bool include_miss) {
    check((roll < 10000), "Roll outside range");

    unsigned range = 0;

    if (include_miss && roll < this->miss_range)
        return PhysicalAttackResult::MISS;
    range += include_miss ? miss_range : 0;

    if (include_dodge && roll < (range + this->dodge_range))
        return PhysicalAttackResult::DODGE;
    range += include_dodge ? dodge_range : 0;

    if (include_block && roll < (range + this->block_range)) {
        if (random->get_roll() < range + crit_chance)
            return PhysicalAttackResult::BLOCK_CRITICAL;
        return PhysicalAttackResult::BLOCK;
    }
    range += include_block ? block_range : 0;

    if (roll < range + crit_chance)
        return PhysicalAttackResult::CRITICAL;

    return PhysicalAttackResult::HIT;
}

void RangedWhiteHitTable::update_miss_chance(const unsigned miss) {
    this->miss_range = miss;
}

void RangedWhiteHitTable::update_dodge_chance(const double dodge) {
    this->dodge_range = static_cast<unsigned>(round(dodge * 10000));
}

void RangedWhiteHitTable::update_block_chance(const double block) {
    this->block_range = static_cast<unsigned>(round(block * 10000));
}
