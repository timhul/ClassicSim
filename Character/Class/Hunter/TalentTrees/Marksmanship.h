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
    Talent* get_improved_hunters_mark();
    Talent* get_lethal_shots();
    Talent* get_aimed_shot();
    Talent* get_mortal_shots();
    Talent* get_barrage();
    Talent* get_ranged_weapon_specialization();
    Talent* get_trueshot_aura();

private:
    Hunter* hunter;
    HunterSpells* spells;
};

#endif // MARKSMANSHIP_H
