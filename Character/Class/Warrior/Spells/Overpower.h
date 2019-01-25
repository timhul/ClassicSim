#ifndef OVERPOWER_H
#define OVERPOWER_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class Overpower: public Spell, public TalentRequirer {
public:
    Overpower(Character* pchar);

protected:
private:
    Warrior* warr;
    QVector<double> talent_ranks;
    double crit_mod;

    bool is_ready_spell_specific() const override;
    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // OVERPOWER_H
