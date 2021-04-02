#pragma once

#include "TalentTree.h"

class Priest;
class PriestSpells;

class Holy : public TalentTree {
public:
    Holy(Priest* priest);

private:
    Priest* priest;
    PriestSpells* spells;

};
