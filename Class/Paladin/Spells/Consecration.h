#ifndef CONSECRATION_H
#define CONSECRATION_H

#include "Spell.h"
#include "TalentRequirer.h"
#include <QVector>

class Buff;
class Paladin;

class Consecration: public Spell, public TalentRequirer {
public:
    Consecration(Paladin* pchar,
                 CooldownControl* cooldown_control,
                 const int spell_rank,
                 const unsigned resource_cost,
                 const unsigned full_duration_dmg);
    ~Consecration() override;

    void perform_periodic() override;
    bool is_rank_learned() const override;

private:
    Buff* buff;
    unsigned ticks {0};
    unsigned full_duration_dmg;
    double tick_rest {0};

    void calculate_damage();

    void spell_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // CONSECRATION_H
