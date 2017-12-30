#ifndef OVERPOWER_H
#define OVERPOWER_H

#include "Spell.h"
#include "CooldownReady.h"

class Overpower: public Spell {
public:
    Overpower(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Overpower", engine, pchar, roll, 5.0, 5) {}

    int spell_effect(const int) const override;
protected:
private:
};

#endif // OVERPOWER_H
