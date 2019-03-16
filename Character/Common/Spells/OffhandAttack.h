#ifndef OFFHANDATTACK_H
#define OFFHANDATTACK_H

#include "Spell.h"
#include "TalentRequirer.h"

class OffhandAttack: public Spell {
public:
    OffhandAttack(Character* pchar);

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void complete_swing();
    void reset_swingtimer();

    virtual void extra_attack();

protected:
    double next_expected_use;
    int iteration;
    double offhand_penalty;

    virtual void spell_effect() override;
    void reset_effect() override;

    virtual void calculate_damage(const bool);

private:
};

#endif // OFFHANDATTACK_H
