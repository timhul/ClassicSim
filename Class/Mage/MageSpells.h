#pragma once

#include "CharacterSpells.h"

class Combustion;
class Ignite;
class Mage;

class MageSpells: public CharacterSpells {
public:
    MageSpells(Mage* mage);

    void inflict_ignite(const double damage);

    Combustion* get_combustion() const;

private:
    Mage* mage;

    Combustion* combustion;
    Ignite* ignite;
};
