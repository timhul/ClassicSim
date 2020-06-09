#pragma once

#include "Spell.h"

class MainhandAttack : public Spell {
public:
    MainhandAttack(Character* pchar);
    ~MainhandAttack() override;

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    void update_next_expected_use_for_parry();
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void complete_swing();
    void reset_swingtimer();
    void add_next_mh_attack();
    virtual void extra_attack();

protected:
    double next_expected_use;
    int iteration;
    QVector<double> talent_ranks;

    virtual void spell_effect() override;
    void reset_effect() override;

    virtual void calculate_damage();

private:
    void prepare_set_of_combat_iterations_spell_specific() override;
};
