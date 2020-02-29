#pragma once

#include "TalentTree.h"

class Warlock;
class WarlockSpells;

class Demonology : public TalentTree {
public:
    Demonology(Warlock* warlock);

private:
    Warlock* warlock;
    WarlockSpells* spells;

    void add_demonic_sacrifice(QMap<QString, Talent*>& talent_tier);
};
