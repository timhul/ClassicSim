#ifndef HEROICSTRIKE_H
#define HEROICSTRIKE_H

#include "Spell.h"
#include "TalentRequirer.h"

class Warrior;

class HeroicStrike: public Spell, public TalentRequirer {
public:
    HeroicStrike(Character* pchar);

    void calculate_damage();

protected:
private:
    friend class ImprovedHeroicStrike;

    Warrior* warr;
    QVector<int> spell_ranks;
    QVector<int> talent_ranks;
    int additional_dmg;

    void spell_effect() override;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // HEROICSTRIKE_H
