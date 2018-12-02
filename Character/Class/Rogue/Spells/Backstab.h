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

    Rogue* rogue;
    double crit_modifier;
    QVector<double> talent_ranks;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // BACKSTAB_H
