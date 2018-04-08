#ifndef HEROICSTRIKE_H
#define HEROICSTRIKE_H

#include "Spell.h"

class Warrior;

class HeroicStrike: public Spell {
public:
    HeroicStrike(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
protected:
private:
    Warrior* pchar;
};

#endif // HEROICSTRIKE_H
