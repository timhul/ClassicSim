
#include "WhiteHitTable.h"
#include "Random.h"
#include <QDebug>

WhiteHitTable::WhiteHitTable(Random *random, const int wpn_skill, const double miss, const double dodge, const double parry,
                             const double glancing, const double block,  const double critical) :
    random(random),
    wpn_skill(wpn_skill),
    miss(miss),
    dodge(dodge),
    parry(parry),
    glancing(glancing),
    block(block),
    critical(critical)
{
    update_ranges();
}

int WhiteHitTable::get_wpn_skill() {
    return wpn_skill;
}

void WhiteHitTable::update_ranges() {
    assert(int(round(miss * 10000)) >= 0);
    assert(int(round(dodge * 10000)) >= 0);
    assert(int(round(parry * 10000)) >= 0);
    assert(int(round(block * 10000)) >= 0);
    assert(int(round(glancing * 10000)) >= 0);
    assert(int(round(critical * 10000)) >= 0);

    this->miss_range = static_cast<unsigned>(round(miss * 10000));
    this->dodge_range = static_cast<unsigned>(round(dodge * 10000));
    this->parry_range = static_cast<unsigned>(round(parry * 10000));
    this->glancing_range = static_cast<unsigned>(round(glancing * 10000));
    this->block_range = static_cast<unsigned>(round(block * 10000));
    this->critical_range = static_cast<unsigned>(round(critical * 10000));
}

int WhiteHitTable::get_outcome(const unsigned roll,
                               const double crit_mod,
                               const bool include_dodge,
                               const bool include_parry,
                               const bool include_block,
                               const bool include_miss) {
    assert(roll < 10000);

    unsigned range = 0;

    if (include_miss && roll < this->miss_range)
        return AttackResult::MISS;
    range += include_miss ? miss_range : 0;

    if (include_dodge && roll < (range + this->dodge_range))
        return AttackResult::DODGE;
    range += include_dodge ? dodge_range : 0;

    if (include_parry && roll < (range + this->parry_range))
        return AttackResult::PARRY;
    range += include_parry ? parry_range : 0;

    if (roll < (range + this->glancing_range))
        return AttackResult::GLANCING;
    range += glancing_range;

    if (include_block && roll < (range + this->block_range)) {
        if (random->get_roll() < range + this->critical_range + static_cast<unsigned>(round(crit_mod * 10000)))
            return AttackResult::BLOCK_CRITICAL;
        return AttackResult::BLOCK;
    }
    range += include_block ? block_range : 0;

    if (roll < (range + this->critical_range + static_cast<unsigned>(round(crit_mod * 10000))))
        return AttackResult::CRITICAL;

    return AttackResult::HIT;
}

void WhiteHitTable::dump_table(void) {
    qDebug() << QString("------ WHITE HIT TABLE %1 WEAPON SKILL ------").arg(wpn_skill);
    qDebug() << "MISS RANGE " << miss_range;
    qDebug() << "DODGE RANGE " << dodge_range;
    qDebug() << "PARRY RANGE " << parry_range;
    qDebug() << "GLANCING RANGE " << glancing_range;
    qDebug() << "BLOCK RANGE " << block_range;
    qDebug() << "CRITICAL RANGE " << critical_range;
}

void WhiteHitTable::update_crit_chance(const double critical) {
    this->critical = critical;
    update_ranges();
}

void WhiteHitTable::update_miss_chance(const double miss) {
    this->miss = miss;
    update_ranges();
}

void WhiteHitTable::update_dodge_chance(const double dodge) {
    this->dodge = dodge;
    update_ranges();
}

void WhiteHitTable::update_parry_chance(const double parry) {
    this->parry = parry;
    update_ranges();
}

void WhiteHitTable::update_glancing_chance(const double glancing) {
    this->glancing = glancing;
    update_ranges();
}

void WhiteHitTable::update_block_chance(const double block) {
    this->block = block;
    update_ranges();
}
