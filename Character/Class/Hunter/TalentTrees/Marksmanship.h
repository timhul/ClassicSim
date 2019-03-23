#ifndef MARKSMANSHIP_H
#define MARKSMANSHIP_H

#include "TalentTree.h"

class Hunter;
class HunterSpells;
class Talent;

class Marksmanship: public TalentTree {
public:
    Marksmanship(Hunter* pchar);
    ~Marksmanship() override = default;

    Talent* get_efficiency();
    Talent* get_aimed_shot();

private:
    Hunter* hunter;
    HunterSpells* spells;
};

#endif // MARKSMANSHIP_H
