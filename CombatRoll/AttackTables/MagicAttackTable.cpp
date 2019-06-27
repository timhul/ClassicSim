#include "MagicAttackTable.h"

#include "Mechanics.h"
#include "Random.h"
#include "Utils/Check.h"

MagicAttackTable::MagicAttackTable(Mechanics* mechanics, Random* random, const unsigned clvl, const unsigned spell_hit, const int target_res) :
    mechanics(mechanics),
    random(random),
    miss_range(0),
    full_resist(0),
    partial_75(0),
    partial_50(0),
    partial_25(0)
{
    update_miss_chance(clvl, spell_hit);
    update_target_resistance(target_res);
}

int MagicAttackTable::get_hit_outcome(const unsigned roll, const unsigned crit_chance) const
{
    if (roll < miss_range)
        return MagicAttackResult::MISS;

    if (random->get_roll() < crit_chance)
        return MagicAttackResult::CRITICAL;

    return MagicAttackResult::HIT;
}

int MagicAttackTable::get_resist_outcome(const unsigned roll) const {
    if (roll < full_resist)
        return MagicResistResult::FULL_RESIST;

    if (roll < partial_75)
        return MagicResistResult::PARTIAL_RESIST_75;

    if (roll < partial_50)
        return MagicResistResult::PARTIAL_RESIST_50;

    if (roll < partial_25)
        return MagicResistResult::PARTIAL_RESIST_25;

    return MagicResistResult::NO_RESIST;
}

void MagicAttackTable::update_miss_chance(const unsigned clvl, const unsigned spell_hit) {
    double miss_chance = mechanics->get_spell_miss_chance_from_lvl_diff(clvl, static_cast<double>(spell_hit) / 10000);
    this->miss_range = static_cast<unsigned>(round(miss_chance * 10000));
}

void MagicAttackTable::update_target_resistance(const int target_resistance) {
    check((target_resistance >= 0), "Target resistance must be a positive value");

    full_resist = static_cast<unsigned>(round(Mechanics::get_full_resist_chance(target_resistance) * 10000));
    partial_75 = full_resist + static_cast<unsigned>(round(Mechanics::get_partial_75_chance(target_resistance) * 10000));
    partial_50 = partial_75 + static_cast<unsigned>(round(Mechanics::get_partial_50_chance(target_resistance) * 10000));
    partial_25 = partial_50 + static_cast<unsigned>(round(Mechanics::get_partial_25_chance(target_resistance) * 10000));
}
