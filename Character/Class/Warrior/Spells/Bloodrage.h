#ifndef BLOODRAGE_H
#define BLOODRAGE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class Bloodrage: public Spell, public TalentRequirer {
public:
    Bloodrage(Character* pchar);

    void perform_periodic() override;

protected:
private:
    friend class ImprovedBloodrage;

    Warrior* warr;
    QVector<unsigned> talent_ranks;
    unsigned immediate_rage_gain;
    int periodic_rage_base;
    int periodic_rage_current;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // BLOODRAGE_H
