#pragma once

#include "TalentTree.h"

class Warlock;
class WarlockSpells;

class Affliction : public TalentTree {
public:
    Affliction(Warlock* warlock);

private:
    Warlock* warlock;
    WarlockSpells* spells;

    void add_improved_life_tap(QMap<QString, Talent*>& talent_tier);
    void add_shadow_mastery(QMap<QString, Talent*>& talent_tier);
};
