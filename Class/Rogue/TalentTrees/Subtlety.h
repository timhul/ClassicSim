#ifndef SUBTLETY_H
#define SUBTLETY_H

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Subtlety: public TalentTree {
public:
    Subtlety(Character *pchar);

    Talent* get_opportunity();
    Talent* get_hemorrhage();

private:
    Rogue* rogue;
    RogueSpells* spells;
};

#endif // SUBTLETY_H
