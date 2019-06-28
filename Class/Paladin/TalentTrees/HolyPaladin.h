#pragma once

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class HolyPaladin: public TalentTree {
public:
    HolyPaladin(Paladin* paladin);
    ~HolyPaladin() override = default;

    Talent* get_divine_strength();
    Talent* get_divine_intellect();
    Talent* get_consecration();

private:
    Paladin* paladin;
    PaladinSpells* spells;
};
