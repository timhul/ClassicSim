#ifndef REND_H
#define REND_H

#include "Spell.h"
#include "TalentRequirer.h"

#include <QVector>

class Buff;
class Warrior;

class Rend: public Spell, public TalentRequirer {
public:
    Rend(Character* pchar);
    ~Rend() override;

private:
    Warrior* warr;
    Buff* buff;
    double talent_modifier;
    double damage_remaining;
    int base_damage;
    double period_tick;
    int max_ticks;
    int num_ticks_left;
    QVector<double> talent_ranks;

    void spell_effect() override;
    void reset_effect() override;
    bool is_ready_spell_specific() const override;
    void perform_periodic() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // REND_H
