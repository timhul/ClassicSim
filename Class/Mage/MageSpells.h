#pragma once

#include "CharacterSpells.h"

class Ignite;
class Mage;

class MageSpells: public CharacterSpells {
public:
    MageSpells(Mage* mage);

    void inflict_ignite(const double damage);

private:
    Mage* mage;

    Ignite* ignite;
};
