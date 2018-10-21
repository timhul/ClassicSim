
#include "StatisticsSpell.h"

#include <utility>

StatisticsSpell::StatisticsSpell(QString name):
    name(std::move(name)),
    percentage_of_total_damage_done(0.0)
{
    this->possible_attempt_outcomes = QSet<Outcome>({
                                                        Outcome::Miss,
                                                        Outcome::FullResist,
                                                        Outcome::Dodge,
                                                        Outcome::Parry,
                                                        Outcome::FullBlock,
                                                        Outcome::PartialResist,
                                                        Outcome::PartialBlock,
                                                        Outcome::PartialBlockCrit,
                                                        Outcome::Glancing,
                                                        Outcome::Hit,
                                                        Outcome::Crit
                                                    });

    this->possible_success_outcomes = QSet<Outcome>({
                                                        Outcome::PartialResist,
                                                        Outcome::PartialBlock,
                                                        Outcome::PartialBlockCrit,
                                                        Outcome::Glancing,
                                                        Outcome::Hit,
                                                        Outcome::Crit
                                                    });
}

StatisticsSpell::~StatisticsSpell() {
    reset();
}

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

int StatisticsSpell::get_attempts(const Outcome outcome) const {
    if (!attempts.contains(outcome))
        return 0;

    return attempts[outcome];
}

int StatisticsSpell::get_misses() const {
    return get_attempts(Outcome::Miss);
}

int StatisticsSpell::get_full_resists() const {
    return get_attempts(Outcome::FullResist);
}

int StatisticsSpell::get_dodges() const {
    return get_attempts(Outcome::Dodge);
}

int StatisticsSpell::get_parries() const  {
    return get_attempts(Outcome::Parry);
}

int StatisticsSpell::get_full_blocks() const  {
    return get_attempts(Outcome::FullBlock);
}

int StatisticsSpell::get_partial_resist() const {
    return get_attempts(Outcome::PartialResist);
}

int StatisticsSpell::get_partial_blocks() const {
    return get_attempts(Outcome::PartialBlock);
}

int StatisticsSpell::get_partial_block_crits() const  {
    return get_attempts(Outcome::PartialBlockCrit);
}

int StatisticsSpell::get_glances() const  {
    return get_attempts(Outcome::Glancing);
}

int StatisticsSpell::get_hits() const {
    return get_attempts(Outcome::Hit);
}

int StatisticsSpell::get_crits() const  {
    return get_attempts(Outcome::Crit);
}

int StatisticsSpell::get_dmg(const Outcome outcome) const {
    if (!damage.contains(outcome))
        return 0;

    return damage[outcome];
}

int StatisticsSpell::get_partial_resist_dmg() const {
    return get_dmg(Outcome::PartialResist);
}

int StatisticsSpell::get_partial_block_dmg() const {
    return get_dmg(Outcome::PartialBlock);
}

int StatisticsSpell::get_partial_block_crit_dmg() const {
    return get_dmg(Outcome::PartialBlockCrit);
}

int StatisticsSpell::get_glancing_dmg() const {
    return get_dmg(Outcome::Glancing);
}

int StatisticsSpell::get_hit_dmg() const  {
    return get_dmg(Outcome::Hit);
}

int StatisticsSpell::get_crit_dmg() const  {
    return get_dmg(Outcome::Crit);
}

// TODO: Instead of returning int, return QSet of Outcome and build superset in Statistics.
int StatisticsSpell::get_num_attempt_columns() const {
    int columns = 0;

    for (auto & outcome : possible_attempt_outcomes) {
        if (get_attempts(outcome) > 0)
            ++columns;
    }

    return columns;
}

// TODO: Instead of returning int, return QSet of Outcome and build superset in Statistics.
int StatisticsSpell::get_num_dmg_columns() const {
    int columns = 0;

    for (auto & outcome : possible_success_outcomes) {
        if (get_dmg(outcome) > 0)
            ++columns;
    }

    return columns;
}

int StatisticsSpell::get_total_dmg_dealt() const {
    int sum = 0;

    for (auto & outcome : possible_success_outcomes) {
        sum += get_dmg(outcome);
    }

    return sum;
}

int StatisticsSpell::get_total_attempts_made() const {
    int sum = 0;

    for (auto & outcome : possible_attempt_outcomes) {
        sum += get_attempts(outcome);
    }

    return sum;
}

double StatisticsSpell::get_percentage_of_damage_dealt() const {
    return this->percentage_of_total_damage_done;
}

void StatisticsSpell::set_percentage_of_damage_dealt(long long int total_damage_dealt) {
    this->percentage_of_total_damage_done = double(get_total_dmg_dealt()) / total_damage_dealt;
}

void StatisticsSpell::add(const StatisticsSpell* other) {
    for (auto & outcome : possible_attempt_outcomes) {
        if (!other->attempts.contains(outcome))
            continue;

        if (!this->attempts.contains(outcome))
            this->attempts.insert(outcome, 0);

        this->attempts[outcome] += other->attempts[outcome];
    }

    for (auto & outcome : possible_success_outcomes) {
        if (!other->damage.contains(outcome))
            continue;

        if (!this->damage.contains(outcome))
            this->damage.insert(outcome, 0);

        this->damage[outcome] += other->damage[outcome];
    }
}
