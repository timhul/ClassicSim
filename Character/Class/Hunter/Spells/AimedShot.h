#ifndef AIMEDSHOT_H
#define AIMEDSHOT_H

#include "SpellCastingTime.h"
#include "TalentRequirer.h"

class AimedShot: public SpellCastingTime, public TalentRequirer {
public:
    AimedShot(Character* pchar);

private:
    const unsigned base_casting_time_ms;
    QVector<double> talent_ranks;
    double resource_base;
    QVector<double> efficiency_ranks;
    double mortal_shots_bonus;
    QVector<double> mortal_shots_ranks;

    void spell_effect() override;
    void complete_cast_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};


#endif // AIMEDSHOT_H
