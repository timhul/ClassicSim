#ifndef COMBAT_H
#define COMBAT_H

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Combat: public TalentTree {
public:
    Combat(Character *pchar);

    Talent* get_adrenaline_rush();

private:
    Rogue* rogue;
    RogueSpells* spells;
};

#endif // COMBAT_H
