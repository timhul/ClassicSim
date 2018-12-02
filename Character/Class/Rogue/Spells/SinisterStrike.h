#ifndef SINISTERSTRIKE_H
#define SINISTERSTRIKE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Rogue;

class SinisterStrike: public Spell, public TalentRequirer {
public:
    SinisterStrike(Character* pchar);

protected:
private:
    friend class Aggression;
    friend class ImprovedSinisterStrike;

    Rogue* rogue;
    double aggression_modifier;
    QVector<int> imp_ss_ranks;
    QVector<double> aggression_ranks;

    void spell_effect() override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // SINISTERSTRIKE_H
