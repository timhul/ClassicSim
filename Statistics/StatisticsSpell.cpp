
#include "StatisticsSpell.h"

#include <utility>

StatisticsSpell::StatisticsSpell(QString name):
    name(std::move(name))
{}

void StatisticsSpell::reset() {
    attempts.clear();
    damage.clear();
}

QString StatisticsSpell::get_name() const {
    return this->name;
}

void StatisticsSpell::increment(const Outcome outcome) {
    if (!attempts.contains(outcome))
        attempts[outcome] = 0;

    attempts[outcome]++;
}

void StatisticsSpell::increment_miss() {
    increment(Outcome::Miss);
}

void StatisticsSpell::increment_full_resist() {
    increment(Outcome::FullResist);
}

void StatisticsSpell::increment_dodge() {
    increment(Outcome::Dodge);
}

void StatisticsSpell::increment_parry() {
    increment(Outcome::Parry);
}

void StatisticsSpell::increment_full_block() {
    increment(Outcome::FullBlock);
}

void StatisticsSpell::increment_partial_resist() {
    increment(Outcome::PartialResist);
}

void StatisticsSpell::increment_partial_block() {
    increment(Outcome::PartialBlock);
}

void StatisticsSpell::increment_partial_block_crit() {
    increment(Outcome::PartialBlockCrit);
}

void StatisticsSpell::increment_glancing() {
    increment(Outcome::Glancing);
}

void StatisticsSpell::increment_hit() {
    increment(Outcome::Hit);
}

void StatisticsSpell::increment_crit() {
    increment(Outcome::Crit);
}

void StatisticsSpell::add_dmg(const Outcome outcome, const int dmg) {
    if (!damage.contains(outcome))
        damage[outcome] = 0;

    damage[outcome] += dmg;
}

void StatisticsSpell::add_partial_resist_dmg(const int dmg) {
    increment_partial_resist();
    add_dmg(Outcome::PartialResist, dmg);
}

void StatisticsSpell::add_partial_block_dmg(const int dmg) {
    increment_partial_block();
    add_dmg(Outcome::PartialBlock, dmg);
}

void StatisticsSpell::add_partial_block_crit_dmg(const int dmg) {
    increment_partial_block_crit();
    add_dmg(Outcome::PartialBlockCrit, dmg);
}

void StatisticsSpell::add_glancing_dmg(const int dmg) {
    increment_glancing();
    add_dmg(Outcome::Glancing, dmg);
}

void StatisticsSpell::add_hit_dmg(const int dmg) {
    increment_hit();
    add_dmg(Outcome::Hit, dmg);
}

void StatisticsSpell::add_crit_dmg(const int dmg) {
    increment_crit();
    add_dmg(Outcome::Crit, dmg);
}

int StatisticsSpell::get_attempts(const Outcome outcome) {
    if (!attempts.contains(outcome))
        return 0;

    return attempts[outcome];
}

int StatisticsSpell::get_misses() {
    return get_attempts(Outcome::Miss);
}

int StatisticsSpell::get_full_resists() {
    return get_attempts(Outcome::FullResist);
}

int StatisticsSpell::get_dodges() {
    return get_attempts(Outcome::Dodge);
}

int StatisticsSpell::get_parries()  {
    return get_attempts(Outcome::Parry);
}

int StatisticsSpell::get_full_blocks()  {
    return get_attempts(Outcome::FullBlock);
}

int StatisticsSpell::get_partial_resist() {
    return get_attempts(Outcome::PartialResist);
}

int StatisticsSpell::get_partial_blocks() {
    return get_attempts(Outcome::PartialBlock);
}

int StatisticsSpell::get_partial_block_crits()  {
    return get_attempts(Outcome::PartialBlockCrit);
}

int StatisticsSpell::get_glancings()  {
    return get_attempts(Outcome::Glancing);
}

int StatisticsSpell::get_hits() {
    return get_attempts(Outcome::Hit);
}

int StatisticsSpell::get_crits()  {
    return get_attempts(Outcome::Crit);
}

int StatisticsSpell::get_dmg(const Outcome outcome) {
    if (!damage.contains(outcome))
        return 0;

    return damage[outcome];
}

int StatisticsSpell::get_partial_resist_dmg() {
    return get_dmg(Outcome::PartialResist);
}

int StatisticsSpell::get_partial_block_dmg() {
    return get_dmg(Outcome::PartialBlock);
}

int StatisticsSpell::get_partial_block_crit_dmg() {
    return get_dmg(Outcome::PartialBlockCrit);
}

int StatisticsSpell::get_glancing_dmg() {
    return get_dmg(Outcome::Glancing);
}

int StatisticsSpell::get_hit_dmg()  {
    return get_dmg(Outcome::Hit);
}

int StatisticsSpell::get_crit_dmg()  {
    return get_dmg(Outcome::Crit);
}

// TODO: Instead of returning int, return QSet of Outcome and build superset in Statistics.
int StatisticsSpell::get_num_attempt_columns() {
    QVector<Outcome> outcomes = {
        Outcome::Miss, Outcome::FullResist, Outcome::Dodge, Outcome::Parry,
        Outcome::FullBlock, Outcome::PartialResist, Outcome::PartialBlock,
        Outcome::PartialBlockCrit, Outcome::Glancing, Outcome::Hit, Outcome::Crit
    };

    int columns = 0;

    for (auto & outcome : outcomes) {
        if (get_attempts(outcome) > 0)
            ++columns;
    }

    return columns;
}

// TODO: Instead of returning int, return QSet of Outcome and build superset in Statistics.
int StatisticsSpell::get_num_dmg_columns() {
    QVector<Outcome> outcomes = {Outcome::PartialResist, Outcome::PartialBlock,
                                 Outcome::PartialBlockCrit, Outcome::Glancing, Outcome::Hit,
                                 Outcome::Crit};

    int columns = 0;

    for (auto & outcome : outcomes) {
        if (get_dmg(outcome) > 0)
            ++columns;
    }

    return columns;
}

int StatisticsSpell::get_total_dmg_dealt() {
    QVector<Outcome> outcomes = {Outcome::PartialResist, Outcome::PartialBlock,
                                 Outcome::PartialBlockCrit, Outcome::Glancing, Outcome::Hit,
                                 Outcome::Crit};

    int sum = 0;

    for (auto & outcome : outcomes) {
        sum += get_dmg(outcome);
    }

    return sum;
}

int StatisticsSpell::get_total_attempts_made() {
    QVector<Outcome> outcomes = {
        Outcome::Miss, Outcome::FullResist, Outcome::Dodge, Outcome::Parry,
        Outcome::FullBlock, Outcome::PartialResist, Outcome::PartialBlock,
        Outcome::PartialBlockCrit, Outcome::Glancing, Outcome::Hit, Outcome::Crit
    };

    int sum = 0;

    for (auto & outcome : outcomes) {
        sum += get_attempts(outcome);
    }

    return sum;
}
