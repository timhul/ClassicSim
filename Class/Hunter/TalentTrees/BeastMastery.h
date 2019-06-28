#pragma once

#include "TalentTree.h"

class Hunter;
class HunterSpells;

class BeastMastery: public TalentTree {
public:
    BeastMastery(Hunter* hunter);
    ~BeastMastery() override = default;

    Talent* get_improved_aspect_of_the_hawk();
    Talent* get_unleashed_fury();
    Talent* get_ferocity();
    Talent* get_bestial_discipline();
    Talent* get_frenzy();
    Talent* get_bestial_wrath();

private:
    Hunter* hunter;
    HunterSpells* spells;
};
