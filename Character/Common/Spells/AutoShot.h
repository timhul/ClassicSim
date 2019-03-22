#ifndef AUTOSHOT_H
#define AUTOSHOT_H

#include "Spell.h"

class AutoShot: public Spell {
public:
    AutoShot(Character* pchar);

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void pause_shot();
    void continue_shot(const double offset);
    void complete_shot();
    void reset_shot_timer();

private:
    bool paused;
    double next_expected_use;
    int iteration;
    QVector<double> talent_ranks;

    virtual void spell_effect() override;
    void reset_effect() override;

    virtual void calculate_damage(const bool);

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // AUTOSHOT_H
