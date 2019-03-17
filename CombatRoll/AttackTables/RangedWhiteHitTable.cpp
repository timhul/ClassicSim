#include "RangedWhiteHitTable.h"

#include <cassert>
#include <math.h>

#include "Random.h"

RangedWhiteHitTable::RangedWhiteHitTable(Random *random,
                                         const int wpn_skill,
                                         const double miss,
                                         const double dodge,
                                         const double block) :
    random(random),
    wpn_skill(wpn_skill),
    miss(miss),
    dodge(dodge),
    block(block),
    critical(0)
{
    update_ranges();
}

int RangedWhiteHitTable::get_wpn_skill() {
    return wpn_skill;
}

void RangedWhiteHitTable::update_ranges() {
    assert(int(round(miss * 10000)) >= 0);
    assert(int(round(dodge * 10000)) >= 0);
    assert(int(round(block * 10000)) >= 0);

    this->miss_range = static_cast<unsigned>(round(miss * 10000));
    this->dodge_range = static_cast<unsigned>(round(dodge * 10000));
    this->block_range = static_cast<unsigned>(round(block * 10000));
}

int RangedWhiteHitTable::get_outcome(const unsigned roll,
                                     const double crit_chance,
                                     const bool include_dodge,
                                     const bool include_block,
                                     const bool include_miss) {
    assert(roll < 10000);

    unsigned range = 0;

    if (include_miss && roll < this->miss_range)
        return PhysicalAttackResult::MISS;
    range += include_miss ? miss_range : 0;

    if (include_dodge && roll < (range + this->dodge_range))
        return PhysicalAttackResult::DODGE;
    range += include_dodge ? dodge_range : 0;

    if (include_block && roll < (range + this->block_range)) {
        if (random->get_roll() < range + static_cast<unsigned>(round(crit_chance * 10000)))
            return PhysicalAttackResult::BLOCK_CRITICAL;
        return PhysicalAttackResult::BLOCK;
    }
    range += include_block ? block_range : 0;

    if (roll < (range + static_cast<unsigned>(round(crit_chance * 10000))))
        return PhysicalAttackResult::CRITICAL;

    return PhysicalAttackResult::HIT;
}

void RangedWhiteHitTable::update_miss_chance(const double miss) {
    this->miss = miss;
    update_ranges();
}

void RangedWhiteHitTable::update_dodge_chance(const double dodge) {
    this->dodge = dodge;
    update_ranges();
}

void RangedWhiteHitTable::update_block_chance(const double block) {
    this->block = block;
    update_ranges();
}
