
#include "MeleeSpecialTable.h"
#include <QDebug>

MeleeSpecialTable::MeleeSpecialTable(Random* _rand,
        const float miss, const float dodge, const float parry,
        const float block, const float critical):
    random(_rand) {
    assert(miss >= 0);
    assert(dodge >= 0);
    assert(parry >= 0);
    assert(block >= 0);
    assert(critical >= 0);

    this->miss_range = int(round(miss * 10000));
    this->dodge_range = int(round(dodge * 10000)) + miss_range;
    this->parry_range = int(round(parry * 10000)) + dodge_range;
    this->block_range = int(round(block * 10000)) + parry_range;

    // Separate roll.
    this->critical_range = int(round(critical * 10000));
}

int MeleeSpecialTable::get_outcome(const int roll, const float crit_mod) {
    assert(roll >= 0 && roll < 10000);

    if (roll < this->miss_range)
        return Outcome::MISS;
    if (roll < this->dodge_range)
        return Outcome::DODGE;
    if (roll < this->parry_range)
        return Outcome::PARRY;
    if (roll < this->block_range) {
        if (random->get_roll() < this->critical_range + int(round(crit_mod * 10000)))
            return Outcome::BLOCK_CRITICAL;
        return Outcome::BLOCK;
    }
    if (random->get_roll() < this->critical_range + int(round(crit_mod * 10000)))
        return Outcome::CRITICAL;
    return Outcome::HIT;
}

void MeleeSpecialTable::dump_table(void) {
    qDebug() << "------------";
    qDebug() << "MISS RANGE " << miss_range;
    qDebug() << "DODGE RANGE " << dodge_range;
    qDebug() << "PARRY RANGE " << parry_range;
    qDebug() << "BLOCK RANGE " << block_range;
    qDebug() << "CRITICAL RANGE " << critical_range;
}

void MeleeSpecialTable::update_crit_chance(const float critical) {
    this->critical_range = int(round(critical * 10000));
}
