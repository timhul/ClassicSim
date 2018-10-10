#ifndef BERSERKERRAGE_H
#define BERSERKERRAGE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class BerserkerRage: public Spell, public TalentRequirer {
public:
    BerserkerRage(Character* pchar);

protected:
private:
    friend class ImprovedBerserkerRage;

    Warrior* warr;
    QVector<unsigned> talent_ranks;
    unsigned rage_gain;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // BERSERKERRAGE_H
