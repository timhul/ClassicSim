#ifndef PRIESTSPELLS_H
#define PRIESTSPELLS_H

#include "CharacterSpells.h"

class Priest;

class PriestSpells: public CharacterSpells {
public:
    PriestSpells(Priest *priest);
    ~PriestSpells() override;

private:
    Priest* priest;
};

#endif // PRIESTSPELLS_H
