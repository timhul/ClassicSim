#ifndef STATISTICSSPELL_H
#define STATISTICSSPELL_H

#include <QString>
#include <QMap>
#include <QSet>
#include <QVector>
#include <math.h>

class StatisticsSpell {
public:
    enum Outcome {
        Miss = 0,
        FullResist,
        Dodge,
        Parry,
        FullBlock,
        PartialResist,
        PartialBlock,
        PartialBlockCrit,
        Glancing,
        Hit,
        Crit
    };

    StatisticsSpell(QString name);
    ~StatisticsSpell();

    void reset();

    QString get_name() const;

    void increment_miss();
    void increment_full_resist();

    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void increment_partial_resist();
    void increment_partial_block();
    void increment_partial_block_crit();

    void increment_glancing();
    void increment_hit();
    void increment_crit();

    void add_partial_resist_dmg(const int);
    void add_partial_block_dmg(const int);
    void add_partial_block_crit_dmg(const int);
    void add_glancing_dmg(const int);
    void add_hit_dmg(const int);
    void add_crit_dmg(const int);

    int get_misses();
    int get_full_resists();
    int get_dodges();
    int get_parries();
    int get_full_blocks();

    int get_partial_resist();
    int get_partial_blocks();
    int get_partial_block_crits();

    int get_glancings();
    int get_hits();
    int get_crits();

    int get_partial_resist_dmg();
    int get_partial_block_dmg();
    int get_partial_block_crit_dmg();

    int get_glancing_dmg();
    int get_hit_dmg();
    int get_crit_dmg();

    int get_num_attempt_columns();
    int get_num_dmg_columns() const;

    int get_total_dmg_dealt() const;
    int get_total_attempts_made();

    double get_percentage_of_damage_dealt() const;
    void set_percentage_of_damage_dealt(long long int);

    void add(const StatisticsSpell*);

protected:
private:
    const QString name;
    double percentage_of_total_damage_done;

    int get_attempts(const Outcome);
    int get_dmg(const Outcome) const;
    void increment(const Outcome);
    void add_dmg(const Outcome outcome, const int dmg);

    QSet<Outcome> possible_attempt_outcomes;
    QSet<Outcome> possible_success_outcomes;

    QMap<Outcome, int> attempts;
    QMap<Outcome, int> damage;
};

#endif // STATISTICSSPELL_H
