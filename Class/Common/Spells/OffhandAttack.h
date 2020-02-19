#pragma once

#include "Spell.h"
#include "TalentRequirer.h"

class OffhandAttack : public Spell {
public:
    OffhandAttack(Character* pchar);
    ~OffhandAttack() override;

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void complete_swing();
    void reset_swingtimer();
    void add_next_oh_attack();
    void extra_attack();

protected:
    double next_expected_use;
    int iteration;
    double offhand_penalty;

    virtual void spell_effect() override;
    void reset_effect() override;

    virtual void calculate_damage();

private:
    void prepare_set_of_combat_iterations_spell_specific() override;
};
