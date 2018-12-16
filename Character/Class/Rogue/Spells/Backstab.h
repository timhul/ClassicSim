#ifndef BACKSTAB_H
#define BACKSTAB_H

#include "Spell.h"
#include "TalentRequirer.h"

class Rogue;

class Backstab: public Spell, public TalentRequirer {
public:
    Backstab(Character* pchar);

protected:
private:
    friend class ImprovedBackstab;
    friend class Lethality;
    friend class Opportunity;

    Rogue* rogue;
    double improved_bs;
    double lethality;
    double opportunity;
    QVector<double> imp_bs_ranks;
    QVector<double> lethality_ranks;
    QVector<double> opportunity_ranks;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // BACKSTAB_H
