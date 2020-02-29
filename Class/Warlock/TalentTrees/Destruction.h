#pragma once

#include "TalentTree.h"

class Warlock;
class WarlockSpells;

class Destruction : public TalentTree {
public:
    Destruction(Warlock* warlock);

private:
    Warlock* warlock;
    WarlockSpells* spells;

    void add_emberstorm(QMap<QString, Talent*>& talent_tier);
};
