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

    void add_improved_shadow_bolt(QMap<QString, Talent*>& talent_tier);
    void add_cataclysm(QMap<QString, Talent*>& talent_tier);
    void add_bane(QMap<QString, Talent*>& talent_tier);
    void add_devastation(QMap<QString, Talent*>& talent_tier);
    void add_ruin(QMap<QString, Talent*>& talent_tier);
    void add_emberstorm(QMap<QString, Talent*>& talent_tier);
};
