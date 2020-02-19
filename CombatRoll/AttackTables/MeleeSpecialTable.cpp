#include "MeleeSpecialTable.h"

#include <cmath>

#include "Random.h"
#include "Utils/Check.h"

MeleeSpecialTable::MeleeSpecialTable(
    Random* _rand, const unsigned wpn_skill, const unsigned miss, const double dodge, const double parry, const double block) :
    wpn_skill(wpn_skill), random(_rand), miss_range(miss) {
    update_dodge_chance(dodge);
    update_parry_chance(parry);
    update_block_chance(block);
}

int MeleeSpecialTable::get_outcome(const unsigned roll,
                                   const unsigned crit_chance,
                                   const bool include_dodge,
                                   const bool include_parry,
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

    if (include_parry && roll < (range + this->parry_range))
        return PhysicalAttackResult::PARRY;
    range += include_parry ? parry_range : 0;

    if (include_block && roll < (range + this->block_range)) {
        if (random->get_roll() < static_cast<unsigned>((round(crit_chance * 10000))))
            return PhysicalAttackResult::BLOCK_CRITICAL;
        return PhysicalAttackResult::BLOCK;
    }
    range += include_block ? block_range : 0;

    if (random->get_roll() < crit_chance)
        return PhysicalAttackResult::CRITICAL;

    return PhysicalAttackResult::HIT;
}

void MeleeSpecialTable::update_miss_chance(const unsigned miss) {
    this->miss_range = miss;
}

void MeleeSpecialTable::update_dodge_chance(const double dodge) {
    this->dodge_range = static_cast<unsigned>(round(dodge * 10000));
}

void MeleeSpecialTable::update_parry_chance(const double parry) {
    this->parry_range = static_cast<unsigned>(round(parry * 10000));
}

void MeleeSpecialTable::update_block_chance(const double block) {
    this->block_range = static_cast<unsigned>(round(block * 10000));
}
