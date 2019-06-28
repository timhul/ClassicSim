#pragma once

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
    Talent* get_lightning_reflexes();

private:
    Hunter* hunter;
    HunterSpells* spells;
};
