#pragma once

#include "CharacterSpells.h"

class Priest;

class PriestSpells: public CharacterSpells {
public:
    PriestSpells(Priest *priest);
    ~PriestSpells() override;

private:
    Priest* priest;
};
