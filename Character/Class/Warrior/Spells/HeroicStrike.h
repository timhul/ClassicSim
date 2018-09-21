#ifndef HEROICSTRIKE_H
#define HEROICSTRIKE_H

#include "Spell.h"

class Warrior;

class HeroicStrike: public Spell {
public:
    HeroicStrike(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;
    void increase_effect_via_talent() override;
    void decrease_effect_via_talent() override;

    void calculate_damage();

protected:
private:
    Warrior* warr;
    QVector<int> spell_ranks;
    QVector<int> talent_ranks;
    int additional_dmg;
};

#endif // HEROICSTRIKE_H
