#ifndef RETRIBUTION_H
#define RETRIBUTION_H

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class Retribution: public TalentTree {
public:
    Retribution(Paladin* paladin);
    ~Retribution() override = default;

    Talent* get_benediction();
    Talent* get_improved_seal_of_the_crusader();

private:
    Paladin* paladin;
    PaladinSpells* spells;
};

#endif // RETRIBUTION_H
