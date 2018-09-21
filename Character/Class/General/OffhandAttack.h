#ifndef OFFHANDATTACK_H
#define OFFHANDATTACK_H

#include "Spell.h"

class OffhandAttack: public Spell {
public:
    OffhandAttack(Engine* engine, Character* pchar, CombatRoll* roll);

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();
    void reset_effect() override;

    void complete_swing();
    virtual void extra_attack();

protected:
    virtual void spell_effect() override;
    virtual void calculate_damage();
    double next_expected_use;
    int iteration;
    QVector<double> talent_ranks;
private:
};

#endif // OFFHANDATTACK_H
