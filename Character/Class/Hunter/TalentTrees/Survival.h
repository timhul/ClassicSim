#ifndef SURVIVAL_H
#define SURVIVAL_H

#include "TalentTree.h"

class Hunter;
class HunterSpells;

class Survival: public TalentTree {
public:
    Survival(Hunter* pchar);
    ~Survival() override = default;

    Talent* get_monster_slaying();
    Talent* get_humanoid_slaying();
    Talent* get_surefooted();
    Talent* get_killer_instinct();

private:
    Hunter* hunter;
    HunterSpells* spells;
};

#endif // SURVIVAL_H
