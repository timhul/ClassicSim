#pragma once

#include <QMap>
#include <QSet>
#include <QString>
#include <QVector>

#include <math.h>

class StatisticsSpell;

bool name(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool total_damage(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool total_attempts(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool hit_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_hits(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool crit_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_crits(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool glance_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_glances(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool miss_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_misses(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool dodge_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_dodges(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool parry_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_parries(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool partial_25_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_partial_25(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool partial_50_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_partial_50(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool partial_75_percent(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool num_partial_75(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool min_hit(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool avg_hit(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool max_hit(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool min_crit(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool avg_crit(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool max_crit(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool min_glancing(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool avg_glancing(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool max_glancing(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool min_dpr(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool avg_dpr(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool max_dpr(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool min_dpet(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool avg_dpet(StatisticsSpell* lhs, StatisticsSpell* rhs);
bool max_dpet(StatisticsSpell* lhs, StatisticsSpell* rhs);

class StatisticsSpell {
public:
    enum Outcome
    {
        Miss = 0,
        FullResist,
        Dodge,
        Parry,
        FullBlock,
        PartialResist25,
        PartialResist50,
        PartialResist75,
        PartialResistCrit25,
        PartialResistCrit50,
        PartialResistCrit75,
        PartialBlock,
        PartialBlockCrit,
        Glancing,
        Hit,
        Crit,
    };

    StatisticsSpell(QString name, QString icon);
    ~StatisticsSpell();

    void reset();

    QString get_name() const;
    QString get_icon() const;

    void increment_miss();
    void increment_full_resist();

    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void increment_partial_resist25();
    void increment_partial_resist50();
    void increment_partial_resist75();
    void increment_partial_block();
    void increment_partial_block_crit();

    void increment_glancing();
    void increment_hit();
    void increment_crit();

    void add_partial_block_dmg(const int dmg, const double resource_cost, const double execution_time);
    void add_partial_block_crit_dmg(const int dmg, const double resource_cost, const double execution_time);
    void add_glancing_dmg(const int dmg, const double resource_cost, const double execution_time);
    void add_hit_dmg(const int dmg, const double resource_cost, const double execution_time);
    void add_spell_hit_dmg(const int dmg, const double resource_cost, const double execution_time, const int resist_result);
    void add_crit_dmg(const int dmg, const double resource_cost, const double execution_time);
    void add_spell_crit_dmg(const int dmg, const double resource_cost, const double execution_time, const int resist_result);

    int get_misses() const;
    int get_full_resists() const;
    int get_dodges() const;
    int get_parries() const;
    int get_full_blocks() const;

    int get_partial_resists_25() const;
    int get_partial_resists_50() const;
    int get_partial_resists_75() const;
    int get_partial_blocks() const;
    int get_partial_block_crits() const;

    int get_glances() const;
    int get_hits() const;
    int get_hits_including_partial_resists() const;
    int get_crits() const;
    int get_crits_including_partial_resists() const;

    long long get_partial_resist25_dmg() const;
    long long get_partial_resist50_dmg() const;
    long long get_partial_resist75_dmg() const;
    long long get_partial_block_dmg() const;
    long long get_partial_block_crit_dmg() const;

    long long get_glancing_dmg() const;
    long long get_hit_dmg() const;
    long long get_crit_dmg() const;

    int get_min_glancing_dmg() const;
    int get_max_glancing_dmg() const;

    int get_min_hit_dmg() const;
    int get_max_hit_dmg() const;

    int get_min_crit_dmg() const;
    int get_max_crit_dmg() const;

    double get_min_dpr() const;
    double get_avg_dpr() const;
    double get_max_dpr() const;

    double get_min_dpet() const;
    double get_avg_dpet() const;
    double get_max_dpet() const;

    int get_num_attempt_columns() const;
    int get_num_dmg_columns() const;

    long long get_total_dmg_dealt() const;
    int get_total_attempts_made() const;

    double get_percentage_of_damage_dealt() const;
    void set_percentage_of_damage_dealt(long long int);

    void add(const StatisticsSpell*);

private:
    const QString name;
    const QString icon;
    double percentage_of_total_damage_done;
    double min_dpr;
    double max_dpr;
    double avg_dpr;
    bool dpr_set;
    unsigned damage_dealt_successes;

    double min_dpet;
    double max_dpet;
    double avg_dpet;
    bool dpet_set;

    int get_attempts(const Outcome outcome) const;
    int get_attempts(const QSet<Outcome>& outcomes) const;
    long long get_dmg(const Outcome) const;
    int get_min_dmg(const Outcome) const;
    int get_max_dmg(const Outcome) const;
    void increment(const Outcome);
    void add_dmg(const Outcome outcome, const int dmg, const double resource_cost, const double execution_time);
    void add_dpr(const int dmg, const double resource_cost);
    void add_dpet(const int dmg, const double execution_time);

    QSet<Outcome> possible_attempt_outcomes;
    QSet<Outcome> possible_success_outcomes;

    QMap<Outcome, int> attempts;
    QMap<Outcome, long long> damage;
    QMap<Outcome, int> min_damage;
    QMap<Outcome, int> max_damage;
};
