#ifndef CONSECRATION_H
#define CONSECRATION_H

#include "Spell.h"
#include "TalentRequirer.h"
#include <QVector>

class Buff;
class Paladin;

class Consecration: public Spell, public TalentRequirer {
public:
    Consecration(Paladin* pchar, CooldownControl* cooldown_control);
    ~Consecration() override;

    void perform_periodic() override;

private:
    Buff* buff;
    unsigned ticks {0};
    unsigned full_duration_dmg {384};
    double tick_rest {0};

    void calculate_damage();

    void spell_effect() override;
    void reset_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // CONSECRATION_H
