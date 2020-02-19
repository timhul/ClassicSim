#include "StatisticsSpell.h"

#include <utility>

#include "MagicAttackResult.h"
#include "Utils/Check.h"
#include "Utils/CompareDouble.h"

bool name(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_name() < rhs->get_name();
}

bool total_damage(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_dmg = lhs->get_total_dmg_dealt();
    auto rhs_dmg = rhs->get_total_dmg_dealt();

    return lhs_dmg == rhs_dmg ? name(lhs, rhs) : lhs_dmg > rhs_dmg;
}

bool total_attempts(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_total = lhs->get_total_attempts_made();
    auto rhs_total = rhs->get_total_attempts_made();

    return lhs_total == rhs_total ? name(lhs, rhs) : lhs_total > rhs_total;
}

bool hit_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_hit = static_cast<double>(lhs->get_hits()) / lhs->get_total_attempts_made();
    auto rhs_hit = static_cast<double>(rhs->get_hits()) / rhs->get_total_attempts_made();

    return lhs_hit > rhs_hit;
}

bool num_hits(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_hit = lhs->get_hits();
    auto rhs_hit = rhs->get_hits();

    return lhs_hit == rhs_hit ? name(lhs, rhs) : lhs_hit > rhs_hit;
}

bool crit_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_crit = static_cast<double>(lhs->get_crits()) / lhs->get_total_attempts_made();
    auto rhs_crit = static_cast<double>(rhs->get_crits()) / rhs->get_total_attempts_made();

    return lhs_crit > rhs_crit;
}

bool num_crits(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_crit = lhs->get_crits();
    auto rhs_crit = rhs->get_crits();

    return lhs_crit == rhs_crit ? name(lhs, rhs) : lhs_crit > rhs_crit;
}

bool glance_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_glance = static_cast<double>(lhs->get_glances()) / lhs->get_total_attempts_made();
    auto rhs_glance = static_cast<double>(rhs->get_glances()) / rhs->get_total_attempts_made();

    return lhs_glance > rhs_glance;
}

bool num_glances(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_glance = lhs->get_glances();
    auto rhs_glance = rhs->get_glances();

    return lhs_glance == rhs_glance ? name(lhs, rhs) : lhs_glance > rhs_glance;
}

bool miss_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_miss = static_cast<double>(lhs->get_misses()) / lhs->get_total_attempts_made();
    auto rhs_miss = static_cast<double>(rhs->get_misses()) / rhs->get_total_attempts_made();

    return lhs_miss > rhs_miss;
}

bool num_misses(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_miss = lhs->get_misses();
    auto rhs_miss = rhs->get_misses();

    return lhs_miss == rhs_miss ? name(lhs, rhs) : lhs_miss > rhs_miss;
}

bool dodge_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_dodge = static_cast<double>(lhs->get_dodges()) / lhs->get_total_attempts_made();
    auto rhs_dodge = static_cast<double>(rhs->get_dodges()) / rhs->get_total_attempts_made();

    return lhs_dodge > rhs_dodge;
}

bool num_dodges(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_dodge = lhs->get_dodges();
    auto rhs_dodge = rhs->get_dodges();

    return lhs_dodge == rhs_dodge ? name(lhs, rhs) : lhs_dodge > rhs_dodge;
}

bool parry_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_parry = static_cast<double>(lhs->get_parries()) / lhs->get_total_attempts_made();
    auto rhs_parry = static_cast<double>(rhs->get_parries()) / rhs->get_total_attempts_made();

    return lhs_parry > rhs_parry;
}

bool num_parries(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_parry = lhs->get_parries();
    auto rhs_parry = rhs->get_parries();

    return lhs_parry == rhs_parry ? name(lhs, rhs) : lhs_parry > rhs_parry;
}

bool partial_25_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_partial_25 = static_cast<double>(lhs->get_partial_resists_25()) / lhs->get_total_attempts_made();
    auto rhs_partial_25 = static_cast<double>(rhs->get_partial_resists_25()) / rhs->get_total_attempts_made();

    return lhs_partial_25 > rhs_partial_25;
}

bool num_partial_25(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_partial_25 = lhs->get_partial_resists_25();
    auto rhs_partial_25 = rhs->get_partial_resists_25();

    return lhs_partial_25 == rhs_partial_25 ? name(lhs, rhs) : lhs_partial_25 > rhs_partial_25;
}

bool partial_50_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_partial_50 = static_cast<double>(lhs->get_partial_resists_50()) / lhs->get_total_attempts_made();
    auto rhs_partial_50 = static_cast<double>(rhs->get_partial_resists_50()) / rhs->get_total_attempts_made();

    return lhs_partial_50 > rhs_partial_50;
}

bool num_partial_50(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_partial_50 = lhs->get_partial_resists_50();
    auto rhs_partial_50 = rhs->get_partial_resists_50();

    return lhs_partial_50 == rhs_partial_50 ? name(lhs, rhs) : lhs_partial_50 > rhs_partial_50;
}

bool partial_75_percent(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_partial_75 = static_cast<double>(lhs->get_partial_resists_75()) / lhs->get_total_attempts_made();
    auto rhs_partial_75 = static_cast<double>(rhs->get_partial_resists_75()) / rhs->get_total_attempts_made();

    return lhs_partial_75 > rhs_partial_75;
}

bool num_partial_75(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    auto lhs_partial_75 = lhs->get_partial_resists_75();
    auto rhs_partial_75 = rhs->get_partial_resists_75();

    return lhs_partial_75 == rhs_partial_75 ? name(lhs, rhs) : lhs_partial_75 > rhs_partial_75;
}

bool min_hit(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_min_hit_dmg() > rhs->get_min_hit_dmg();
}

bool avg_hit(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return (static_cast<double>(lhs->get_hit_dmg()) / lhs->get_hits()) > (static_cast<double>(rhs->get_hit_dmg()) / rhs->get_hits());
}

bool max_hit(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_max_hit_dmg() > rhs->get_max_hit_dmg();
}

bool min_crit(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_min_crit_dmg() > rhs->get_min_crit_dmg();
}

bool avg_crit(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return (static_cast<double>(lhs->get_crit_dmg()) / lhs->get_crits()) > (static_cast<double>(rhs->get_crit_dmg()) / rhs->get_crits());
}

bool max_crit(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_max_crit_dmg() > rhs->get_max_crit_dmg();
}

bool min_glancing(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_min_glancing_dmg() > rhs->get_min_glancing_dmg();
}

bool avg_glancing(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return (static_cast<double>(lhs->get_glancing_dmg()) / lhs->get_glances()) > (static_cast<double>(rhs->get_glancing_dmg()) / rhs->get_glances());
}

bool max_glancing(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_max_glancing_dmg() > rhs->get_max_glancing_dmg();
}

bool min_dpr(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_min_dpr() > rhs->get_min_dpr();
}

bool avg_dpr(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_avg_dpr() > rhs->get_avg_dpr();
}

bool max_dpr(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_max_dpr() > rhs->get_max_dpr();
}

bool min_dpet(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_min_dpet() > rhs->get_min_dpet();
}

bool avg_dpet(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_avg_dpet() > rhs->get_avg_dpet();
}

bool max_dpet(StatisticsSpell* lhs, StatisticsSpell* rhs) {
    return lhs->get_max_dpet() > rhs->get_max_dpet();
}

StatisticsSpell::StatisticsSpell(QString name, QString icon) :
    name(std::move(name)),
    icon(std::move(icon)),
    percentage_of_total_damage_done(0.0),
    min_dpr(std::numeric_limits<double>::max()),
    max_dpr(std::numeric_limits<double>::min()),
    avg_dpr(0),
    dpr_set(false),
    damage_dealt_successes(0),
    min_dpet(std::numeric_limits<double>::max()),
    max_dpet(std::numeric_limits<double>::min()),
    avg_dpet(0),
    dpet_set(false),
    possible_attempt_outcomes(QSet<Outcome>({Outcome::Miss, Outcome::FullResist, Outcome::Dodge, Outcome::Parry, Outcome::FullBlock,
                                             Outcome::PartialResist25, Outcome::PartialResist50, Outcome::PartialResist75,
                                             Outcome::PartialResistCrit25, Outcome::PartialResistCrit50, Outcome::PartialResistCrit75,
                                             Outcome::PartialBlock, Outcome::PartialBlockCrit, Outcome::Glancing, Outcome::Hit, Outcome::Crit})),
    possible_success_outcomes(QSet<Outcome>({Outcome::PartialResist25, Outcome::PartialResist50, Outcome::PartialResist75,
                                             Outcome::PartialResistCrit25, Outcome::PartialResistCrit50, Outcome::PartialResistCrit75,
                                             Outcome::PartialBlock, Outcome::PartialBlockCrit, Outcome::Glancing, Outcome::Hit, Outcome::Crit})) {}

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

QString StatisticsSpell::get_icon() const {
    return this->icon;
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

void StatisticsSpell::increment_partial_resist25() {
    increment(Outcome::PartialResist25);
}

void StatisticsSpell::increment_partial_resist50() {
    increment(Outcome::PartialResist50);
}

void StatisticsSpell::increment_partial_resist75() {
    increment(Outcome::PartialResist75);
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

void StatisticsSpell::add_dmg(const Outcome outcome, const int dmg, const double resource_cost, const double execution_time) {
    if (!damage.contains(outcome))
        damage[outcome] = 0;

    if (!min_damage.contains(outcome) || min_damage[outcome] > dmg)
        min_damage[outcome] = dmg;

    if (!max_damage.contains(outcome) || max_damage[outcome] < dmg)
        max_damage[outcome] = dmg;

    damage[outcome] += dmg;
    ++damage_dealt_successes;

    add_dpr(dmg, resource_cost);
    add_dpet(dmg, execution_time);
}

void StatisticsSpell::add_dpr(const int dmg, const double resource_cost) {
    if (almost_equal(resource_cost, 0))
        return;

    dpr_set = true;

    double damage_per_resource = double(dmg) / resource_cost;

    if (damage_per_resource < min_dpr)
        min_dpr = damage_per_resource;
    if (damage_per_resource > max_dpr)
        max_dpr = damage_per_resource;

    avg_dpr = avg_dpr + (damage_per_resource - avg_dpr) / damage_dealt_successes;
}

void StatisticsSpell::add_dpet(const int dmg, const double execution_time) {
    if (delta(execution_time, 0) < 0.0001)
        return;

    dpet_set = true;

    double damage_per_execution_time = double(dmg) / execution_time;

    if (damage_per_execution_time < min_dpet)
        min_dpet = damage_per_execution_time;
    if (damage_per_execution_time > max_dpet)
        max_dpet = damage_per_execution_time;

    avg_dpet = avg_dpet + (damage_per_execution_time - avg_dpet) / damage_dealt_successes;
}

void StatisticsSpell::add_partial_block_dmg(const int dmg, const double resource_cost, const double execution_time) {
    increment_partial_block();
    add_dmg(Outcome::PartialBlock, dmg, resource_cost, execution_time);
}

void StatisticsSpell::add_partial_block_crit_dmg(const int dmg, const double resource_cost, const double execution_time) {
    increment_partial_block_crit();
    add_dmg(Outcome::PartialBlockCrit, dmg, resource_cost, execution_time);
}

void StatisticsSpell::add_glancing_dmg(const int dmg, const double resource_cost, const double execution_time) {
    increment_glancing();
    add_dmg(Outcome::Glancing, dmg, resource_cost, execution_time);
}

void StatisticsSpell::add_hit_dmg(const int dmg, const double resource_cost, const double execution_time) {
    increment_hit();
    add_dmg(Outcome::Hit, dmg, resource_cost, execution_time);
}

void StatisticsSpell::add_spell_hit_dmg(const int dmg, const double resource_cost, const double execution_time, const int resist_result) {
    switch (resist_result) {
    case MagicResistResult::NO_RESIST:
        increment_hit();
        add_dmg(Outcome::Hit, dmg, resource_cost, execution_time);
        break;
    case MagicResistResult::PARTIAL_RESIST_25:
        increment(Outcome::PartialResist25);
        add_dmg(Outcome::PartialResist25, dmg, resource_cost, execution_time);
        break;
    case MagicResistResult::PARTIAL_RESIST_50:
        increment(Outcome::PartialResist50);
        add_dmg(Outcome::PartialResist50, dmg, resource_cost, execution_time);
        break;
    case MagicResistResult::PARTIAL_RESIST_75:
        increment(Outcome::PartialResist75);
        add_dmg(Outcome::PartialResist75, dmg, resource_cost, execution_time);
        break;
    default:
        check(false, "StatisticsSpell::add_spell_hit_dmg failed due to unhandled resist result");
    }
}

void StatisticsSpell::add_crit_dmg(const int dmg, const double resource_cost, const double execution_time) {
    increment_crit();
    add_dmg(Outcome::Crit, dmg, resource_cost, execution_time);
}

void StatisticsSpell::add_spell_crit_dmg(const int dmg, const double resource_cost, const double execution_time, const int resist_result) {
    switch (resist_result) {
    case MagicResistResult::NO_RESIST:
        increment_crit();
        add_dmg(Outcome::Crit, dmg, resource_cost, execution_time);
        break;
    case MagicResistResult::PARTIAL_RESIST_25:
        increment(Outcome::PartialResistCrit25);
        add_dmg(Outcome::PartialResistCrit25, dmg, resource_cost, execution_time);
        break;
    case MagicResistResult::PARTIAL_RESIST_50:
        increment(Outcome::PartialResistCrit50);
        add_dmg(Outcome::PartialResistCrit50, dmg, resource_cost, execution_time);
        break;
    case MagicResistResult::PARTIAL_RESIST_75:
        increment(Outcome::PartialResistCrit75);
        add_dmg(Outcome::PartialResistCrit75, dmg, resource_cost, execution_time);
        break;
    default:
        check(false, "StatisticsSpell::add_spell_crit_dmg failed due to unhandled resist result");
    }
}

int StatisticsSpell::get_attempts(const Outcome outcome) const {
    return attempts[outcome];
}

int StatisticsSpell::get_attempts(const QSet<Outcome>& outcomes) const {
    int sum = 0;

    for (const auto& outcome : outcomes)
        sum += get_attempts(outcome);

    return sum;
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

int StatisticsSpell::get_parries() const {
    return get_attempts(Outcome::Parry);
}

int StatisticsSpell::get_full_blocks() const {
    return get_attempts(Outcome::FullBlock);
}

int StatisticsSpell::get_partial_resists_25() const {
    return get_attempts({Outcome::PartialResist25, Outcome::PartialResistCrit25});
}

int StatisticsSpell::get_partial_resists_50() const {
    return get_attempts({Outcome::PartialResist50, Outcome::PartialResistCrit50});
}

int StatisticsSpell::get_partial_resists_75() const {
    return get_attempts({Outcome::PartialResist75, Outcome::PartialResistCrit75});
}

int StatisticsSpell::get_partial_blocks() const {
    return get_attempts(Outcome::PartialBlock);
}

int StatisticsSpell::get_partial_block_crits() const {
    return get_attempts(Outcome::PartialBlockCrit);
}

int StatisticsSpell::get_glances() const {
    return get_attempts(Outcome::Glancing);
}

int StatisticsSpell::get_hits() const {
    return get_attempts(Outcome::Hit);
}

int StatisticsSpell::get_hits_including_partial_resists() const {
    return get_attempts({Outcome::Hit, Outcome::PartialResist25, Outcome::PartialResist50, Outcome::PartialResist75});
}

int StatisticsSpell::get_crits() const {
    return get_attempts(Outcome::Crit);
}

int StatisticsSpell::get_crits_including_partial_resists() const {
    return get_attempts({Outcome::Crit, Outcome::PartialResistCrit25, Outcome::PartialResistCrit50, Outcome::PartialResistCrit75});
}

long long StatisticsSpell::get_dmg(const Outcome outcome) const {
    if (!damage.contains(outcome))
        return 0;

    return damage[outcome];
}

int StatisticsSpell::get_min_dmg(const Outcome outcome) const {
    if (!min_damage.contains(outcome))
        return 0;

    return min_damage[outcome];
}

int StatisticsSpell::get_max_dmg(const Outcome outcome) const {
    if (!max_damage.contains(outcome))
        return 0;

    return max_damage[outcome];
}

long long StatisticsSpell::get_partial_resist25_dmg() const {
    return get_dmg(Outcome::PartialResist25);
}

long long StatisticsSpell::get_partial_resist50_dmg() const {
    return get_dmg(Outcome::PartialResist50);
}

long long StatisticsSpell::get_partial_resist75_dmg() const {
    return get_dmg(Outcome::PartialResist75);
}

long long StatisticsSpell::get_partial_block_dmg() const {
    return get_dmg(Outcome::PartialBlock);
}

long long StatisticsSpell::get_partial_block_crit_dmg() const {
    return get_dmg(Outcome::PartialBlockCrit);
}

long long StatisticsSpell::get_glancing_dmg() const {
    return get_dmg(Outcome::Glancing);
}

long long StatisticsSpell::get_hit_dmg() const {
    return get_dmg(Outcome::Hit);
}

long long StatisticsSpell::get_crit_dmg() const {
    return get_dmg(Outcome::Crit);
}

int StatisticsSpell::get_min_glancing_dmg() const {
    return get_min_dmg(Outcome::Glancing);
}

int StatisticsSpell::get_max_glancing_dmg() const {
    return get_max_dmg(Outcome::Glancing);
}

int StatisticsSpell::get_min_hit_dmg() const {
    return get_min_dmg(Outcome::Hit);
}

int StatisticsSpell::get_max_hit_dmg() const {
    return get_max_dmg(Outcome::Hit);
}

int StatisticsSpell::get_min_crit_dmg() const {
    return get_min_dmg(Outcome::Crit);
}

int StatisticsSpell::get_max_crit_dmg() const {
    return get_max_dmg(Outcome::Crit);
}

double StatisticsSpell::get_min_dpr() const {
    return dpr_set ? this->min_dpr : 0.0;
}

double StatisticsSpell::get_avg_dpr() const {
    return dpr_set ? this->avg_dpr : 0.0;
}

double StatisticsSpell::get_max_dpr() const {
    return dpr_set ? this->max_dpr : 0.0;
}

double StatisticsSpell::get_min_dpet() const {
    return dpet_set ? this->min_dpet : 0.0;
}

double StatisticsSpell::get_avg_dpet() const {
    return dpet_set ? this->avg_dpet : 0.0;
}

double StatisticsSpell::get_max_dpet() const {
    return dpet_set ? this->max_dpet : 0.0;
}

int StatisticsSpell::get_num_attempt_columns() const {
    int columns = 0;

    for (const auto& outcome : possible_attempt_outcomes) {
        if (get_attempts(outcome) > 0)
            ++columns;
    }

    return columns;
}

int StatisticsSpell::get_num_dmg_columns() const {
    int columns = 0;

    for (const auto& outcome : possible_success_outcomes) {
        if (get_dmg(outcome) > 0)
            ++columns;
    }

    return columns;
}

long long StatisticsSpell::get_total_dmg_dealt() const {
    long long sum = 0;

    for (const auto& outcome : possible_success_outcomes) {
        sum += get_dmg(outcome);
    }

    return sum;
}

int StatisticsSpell::get_total_attempts_made() const {
    int sum = 0;

    for (const auto& outcome : possible_attempt_outcomes) {
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
    for (const auto& outcome : possible_attempt_outcomes) {
        if (!other->attempts.contains(outcome))
            continue;

        if (!this->attempts.contains(outcome))
            this->attempts.insert(outcome, 0);

        this->attempts[outcome] += other->attempts[outcome];
    }

    for (const auto& outcome : possible_success_outcomes) {
        if (!other->damage.contains(outcome))
            continue;

        if (!this->damage.contains(outcome))
            this->damage.insert(outcome, 0);

        this->damage[outcome] += other->damage[outcome];

        if (!this->min_damage.contains(outcome) && other->min_damage.contains(outcome))
            this->min_damage[outcome] = other->min_damage[outcome];
        else if (this->min_damage.contains(outcome) && other->min_damage.contains(outcome))
            this->min_damage[outcome] = other->min_damage[outcome] < this->min_damage[outcome] ? other->min_damage[outcome] :
                                                                                                 this->min_damage[outcome];

        if (!this->max_damage.contains(outcome) && other->max_damage.contains(outcome))
            this->max_damage[outcome] = other->max_damage[outcome];
        else if (this->max_damage.contains(outcome) && other->max_damage.contains(outcome))
            this->max_damage[outcome] = other->max_damage[outcome] < this->max_damage[outcome] ? other->max_damage[outcome] :
                                                                                                 this->max_damage[outcome];
    }

    if (this->min_dpr > other->min_dpr)
        this->min_dpr = other->min_dpr;

    if (this->max_dpr < other->max_dpr)
        this->max_dpr = other->max_dpr;

    unsigned total_counter = this->damage_dealt_successes + other->damage_dealt_successes;
    this->avg_dpr = this->avg_dpr * (double(this->damage_dealt_successes) / total_counter)
                    + other->avg_dpr * (double(other->damage_dealt_successes) / total_counter);

    this->dpr_set = this->dpr_set ? true : other->dpr_set;

    if (this->min_dpet > other->min_dpet)
        this->min_dpet = other->min_dpet;

    if (this->max_dpet < other->max_dpet)
        this->max_dpet = other->max_dpet;

    this->avg_dpet = this->avg_dpet * (double(this->damage_dealt_successes) / total_counter)
                     + other->avg_dpet * (double(other->damage_dealt_successes) / total_counter);

    this->dpet_set = this->dpet_set ? true : other->dpet_set;

    this->damage_dealt_successes += other->damage_dealt_successes;
}
