#ifndef OVERPOWER_H
#define OVERPOWER_H

#include "Spell.h"

class Warrior;

class Overpower: public Spell {
public:
    Overpower(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
protected:
private:
    Warrior* pchar;
};

#endif // OVERPOWER_H
