#ifndef MORTALSTRIKE_H
#define MORTALSTRIKE_H

#include "Spell.h"

class Warrior;

class MortalStrike: public Spell {
public:
    MortalStrike(Character* pchar);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
};

#endif // MORTALSTRIKE_H
