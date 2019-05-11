#ifndef PROTECTIONPALADIN_H
#define PROTECTIONPALADIN_H

#include "TalentTree.h"

class Paladin;
class PaladinSpells;

class ProtectionPaladin: public TalentTree {
public:
    ProtectionPaladin(Paladin* paladin);
    ~ProtectionPaladin() override = default;

    Talent* get_precision();
    Talent* get_one_handed_weapon_specialization();

private:
    Paladin* paladin;
    PaladinSpells* spells;
};

#endif // PROTECTIONPALADIN_H
