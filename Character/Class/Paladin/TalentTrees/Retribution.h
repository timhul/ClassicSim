#ifndef RETRIBUTION_H
#define RETRIBUTION_H

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class Retribution: public TalentTree {
public:
    Retribution(Paladin* paladin);
    ~Retribution() override = default;

private:
    Paladin* paladin;
    PaladinSpells* spells;
};

#endif // RETRIBUTION_H
