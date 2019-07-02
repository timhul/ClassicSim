#pragma once

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class ProtectionPaladin: public TalentTree {
public:
    ProtectionPaladin(Paladin* paladin);
    ~ProtectionPaladin() override = default;

private:
    Paladin* paladin;
    PaladinSpells* spells;

    void add_precision(QMap<QString, Talent*>& talent_tier);
    void add_one_handed_weapon_specialization(QMap<QString, Talent*>& talent_tier);
};
