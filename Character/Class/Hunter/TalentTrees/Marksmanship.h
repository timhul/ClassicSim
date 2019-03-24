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
    Talent* get_lethal_shots();
    Talent* get_aimed_shot();
    Talent* get_mortal_shots();

private:
    Hunter* hunter;
    HunterSpells* spells;
};

#endif // MARKSMANSHIP_H
