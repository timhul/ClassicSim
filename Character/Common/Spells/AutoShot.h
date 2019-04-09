#ifndef AUTOSHOT_H
#define AUTOSHOT_H

#include "Spell.h"

class Hunter;

class AutoShot: public Spell {
public:
    AutoShot(Hunter* pchar);

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void reset_shot_timer();

private:
    Hunter* hunter;
    double next_expected_use;
    int iteration;
    QVector<double> talent_ranks;

    virtual void spell_effect() override;
    void reset_effect() override;

    virtual void calculate_damage(const bool);
    void complete_shot();

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // AUTOSHOT_H
