#ifndef HOLYPALADIN_H
#define HOLYPALADIN_H

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class HolyPaladin: public TalentTree {
public:
    HolyPaladin(Paladin* paladin);
    ~HolyPaladin() override = default;

private:
    Paladin* paladin;
    PaladinSpells* spells;
};

#endif // HOLYPALADIN_H
