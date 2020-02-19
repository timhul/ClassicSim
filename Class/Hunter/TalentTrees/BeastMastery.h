#pragma once

#include "TalentTree.h"

class Hunter;
class HunterSpells;

class BeastMastery : public TalentTree {
public:
    BeastMastery(Hunter* hunter);

private:
    Hunter* hunter;
    HunterSpells* spells;

    void add_improved_aspect_of_the_hawk(QMap<QString, Talent*>& talent_tier);
    void add_unleashed_fury(QMap<QString, Talent*>& talent_tier);
    void add_ferocity(QMap<QString, Talent*>& talent_tier);
    void add_bestial_discipline(QMap<QString, Talent*>& talent_tier);
    void add_frenzy(QMap<QString, Talent*>& talent_tier);
    void add_bestial_wrath(QMap<QString, Talent*>& talent_tier);
};
