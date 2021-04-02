#pragma once

#include "TalentTree.h"

class Priest;
class PriestSpells;

class Discipline : public TalentTree {
public:
    Discipline(Priest* priest);

private:
    Priest* priest;
    PriestSpells* spells;

};
