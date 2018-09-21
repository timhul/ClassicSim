
#include "MeleeSpecialTable.h"
#include <QDebug>

MeleeSpecialTable::MeleeSpecialTable(Random* _rand, const int wpn_skill,
                                     const double miss, const double dodge, const double parry,
                                     const double block, const double critical):
    random(_rand),
    wpn_skill(wpn_skill),
    miss(miss),
    dodge(dodge),
    parry(parry),
    block(block),
    critical(critical)
{
    update_ranges();
}

void MeleeSpecialTable::update_ranges() {
    assert(int(round(miss * 10000)) >= 0);
    assert(int(round(dodge * 10000)) >= 0);
    assert(int(round(parry * 10000)) >= 0);
    assert(int(round(block * 10000)) >= 0);
    assert(int(round(critical * 10000)) >= 0);

    this->miss_range = int(round(miss * 10000));
    this->dodge_range = int(round(dodge * 10000));
    this->parry_range = int(round(parry * 10000));
    this->block_range = int(round(block * 10000));

    // Separate roll.
    this->critical_range = int(round(critical * 10000));
    // If not separate roll:
    // this->critical_range = int(round(critical * 10000)) + block_range
    // and change random()->get_roll in get_outcome()
}

int MeleeSpecialTable::get_wpn_skill() {
    return wpn_skill;
}

int MeleeSpecialTable::get_outcome(const int roll,
                                   const double crit_mod,
                                   const bool include_dodge,
                                   const bool include_parry,
                                   const bool include_block,
                                   const bool include_miss) {
    assert(roll >= 0 && roll < 10000);

    int range = 0;

    if (include_miss && roll < this->miss_range)
        return AttackResult::MISS;
    range += include_miss ? miss_range : 0;

    if (include_dodge && roll < (range + this->dodge_range))
        return AttackResult::DODGE;
    range += include_dodge ? dodge_range : 0;

    if (include_parry && roll < (range + this->parry_range))
        return AttackResult::PARRY;
    range += include_parry ? parry_range : 0;

    if (include_block && roll < (range + this->block_range)) {
        if (random->get_roll() < this->critical_range + int(round(crit_mod * 10000)))
            return AttackResult::BLOCK_CRITICAL;
        return AttackResult::BLOCK;
    }
    range += include_block ? block_range : 0;

    if (random->get_roll() < this->critical_range + int(round(crit_mod * 10000)))
        return AttackResult::CRITICAL;

    return AttackResult::HIT;
}

void MeleeSpecialTable::dump_table(void) {
    qDebug() << QString("------ SPECIAL ATTACK TABLE %1 WEAPON SKILL ------").arg(wpn_skill);
    qDebug() << "MISS RANGE " << miss_range;
    qDebug() << "DODGE RANGE " << dodge_range;
    qDebug() << "PARRY RANGE " << parry_range;
    qDebug() << "BLOCK RANGE " << block_range;
    qDebug() << "CRITICAL RANGE " << critical_range;
}

void MeleeSpecialTable::update_crit_chance(const double critical) {
    this->critical = critical;
    update_ranges();
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
