#pragma once

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Assassination: public TalentTree {
public:
    Assassination(Rogue* pchar);

    Talent* get_improved_eviscerate();
    Talent* get_ruthlessness();
    Talent* get_improved_slice_and_dice();
    Talent* get_relentless_strikes();
    Talent* get_lethality();
    Talent* get_vile_poisons();
    Talent* get_improved_poisons();
    Talent* get_seal_fate();

private:
    Rogue* rogue;
    RogueSpells* spells;
};
