#ifndef AUTOSHOT_H
#define AUTOSHOT_H

#include "SetBonusRequirer.h"
#include "Spell.h"

class Hunter;
class StatisticsResource;

class AutoShot: public Spell, public SetBonusRequirer {
public:
    AutoShot(Hunter* pchar);
    ~AutoShot() override;

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void reset_shot_timer();

private:
    Hunter* hunter;
    StatisticsResource* statistics_resource {nullptr};
    double next_expected_use;
    unsigned adrenaline_rush {0};
    int iteration;
    QVector<double> talent_ranks;

    void spell_effect() override;
    void reset_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void add_adrenaline_rush_statistics();

    void calculate_damage();
    void complete_shot();

    void activate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
    void deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) override;
};

#endif // AUTOSHOT_H
