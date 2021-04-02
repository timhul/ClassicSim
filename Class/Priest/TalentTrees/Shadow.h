#pragma once

#include "TalentTree.h"

class Priest;
class PriestSpells;

class Shadow : public TalentTree {
public:
    Shadow(Priest* priest);

private:
    Priest* priest;
    PriestSpells* spells;

};
