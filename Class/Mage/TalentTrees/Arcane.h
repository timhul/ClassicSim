#pragma once

#include "TalentTree.h"

class Mage;
class MageSpells;

class Arcane: public TalentTree {
public:
    Arcane(Mage* mage);
    ~Arcane() override = default;

private:
    Mage* mage;
    MageSpells* spells;
};
