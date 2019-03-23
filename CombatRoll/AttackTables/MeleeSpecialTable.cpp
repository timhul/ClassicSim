#include "MeleeSpecialTable.h"

#include <cmath>

#include "Random.h"
#include "Utils/Check.h"

MeleeSpecialTable::MeleeSpecialTable(Random* _rand,
                                     const int wpn_skill,
                                     const double miss,
                                     const double dodge,
                                     const double parry,
                                     const double block):
    random(_rand),
    wpn_skill(wpn_skill),
    miss(miss),
    dodge(dodge),
    parry(parry),
    block(block)
{
    update_ranges();
}

void MeleeSpecialTable::update_ranges() {
    check((int(round(miss * 10000)) >= 0), "Range must be positive value");
    check((int(round(dodge * 10000)) >= 0), "Range must be positive value");
    check((int(round(parry * 10000)) >= 0), "Range must be positive value");
    check((int(round(block * 10000)) >= 0), "Range must be positive value");

    this->miss_range = static_cast<unsigned>(round(miss * 10000));
    this->dodge_range = static_cast<unsigned>(round(dodge * 10000));
    this->parry_range = static_cast<unsigned>(round(parry * 10000));
    this->block_range = static_cast<unsigned>(round(block * 10000));
}

int MeleeSpecialTable::get_wpn_skill() {
    return wpn_skill;
}

int MeleeSpecialTable::get_outcome(const unsigned roll,
                                   const double crit_chance,
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

    if (random->get_roll() < static_cast<unsigned>((round(crit_chance * 10000))))
        return PhysicalAttackResult::CRITICAL;

    return PhysicalAttackResult::HIT;
}

void MeleeSpecialTable::update_miss_chance(const double miss) {
    this->miss = miss;
    update_ranges();
}

void MeleeSpecialTable::update_dodge_chance(const double dodge) {
    this->dodge = dodge;
    update_ranges();
}

void MeleeSpecialTable::update_parry_chance(const double parry) {
    this->parry = parry;
    update_ranges();
}

void MeleeSpecialTable::update_block_chance(const double block) {
    this->block = block;
    update_ranges();
}
