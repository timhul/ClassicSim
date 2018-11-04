#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Spell.h"
#include "TalentRequirer.h"
#include <QVector>

class Buff;
class Warrior;

class DeepWounds: public Spell, public TalentRequirer {
public:
    DeepWounds(Character* pchar);
    ~DeepWounds() override;

    void perform_periodic() override;

protected:
private:
    friend class DeepWoundsTalent;

    Warrior* warr;
    Buff* buff;
    double wpn_percent;
    double previous_tick_rest;
    QVector<int> stacks;
    QVector<double> talent_ranks;

    void spell_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;

    void enable_spell_effect() override;
    void disable_spell_effect() override;
};

#endif // DEEPWOUNDS_H
