#ifndef BEASTMASTERY_H
#define BEASTMASTERY_H

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

private:
    Hunter* hunter;
    HunterSpells* spells;
};

#endif // BEASTMASTERY_H
