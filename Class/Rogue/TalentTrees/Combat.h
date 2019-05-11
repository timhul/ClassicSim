#ifndef COMBAT_H
#define COMBAT_H

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Combat: public TalentTree {
public:
    Combat(Character *pchar);

    Talent* get_improved_sinister_strike();
    Talent* get_improved_backstab();
    Talent* get_dual_wield_spec();
    Talent* get_blade_flurry();
    Talent* get_sword_spec();
    Talent* get_aggression();
    Talent* get_adrenaline_rush();

private:
    Rogue* rogue;
    RogueSpells* spells;

    Talent* get_endurance();
};

#endif // COMBAT_H
