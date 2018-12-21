#ifndef HEMORRHAGE_H
#define HEMORRHAGE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Rogue;

class Hemorrhage: public Spell, public TalentRequirer {
public:
    Hemorrhage(Character* pchar);

protected:
private:
    friend class HemorrhageTalent;
    friend class Lethality;

    Rogue* rogue;
    double lethality;
    QVector<double> lethality_ranks;

    void spell_effect() override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // HEMORRHAGE_H
