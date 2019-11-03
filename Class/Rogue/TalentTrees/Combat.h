#pragma once

#include "TalentTree.h"

class Rogue;
class RogueSpells;

class Combat: public TalentTree {
public:
    Combat(Rogue* pchar);

private:
    Rogue* rogue;
    RogueSpells* spells;

    void add_endurance(QMap<QString, Talent*>& talent_tier);
    void add_improved_sinister_strike(QMap<QString, Talent*>& talent_tier);
    void add_improved_backstab(QMap<QString, Talent*>& talent_tier);
    void add_dual_wield_spec(QMap<QString, Talent*>& talent_tier);
    void add_blade_flurry(QMap<QString, Talent*>& talent_tier);
    void add_sword_spec(QMap<QString, Talent*>& talent_tier);
    void add_aggression(QMap<QString, Talent*>& talent_tier);
    void add_adrenaline_rush(QMap<QString, Talent*>& talent_tier);
};
