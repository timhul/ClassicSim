#pragma once

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

    void add_divine_strength(QMap<QString, Talent*>& talent_tier);
    void add_divine_intellect(QMap<QString, Talent*>& talent_tier);
    void add_consecration(QMap<QString, Talent*>& talent_tier);
};
