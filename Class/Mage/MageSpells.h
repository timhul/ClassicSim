#pragma once

#include "CharacterSpells.h"

class Mage;

class MageSpells: public CharacterSpells {
public:
    MageSpells(Mage* mage);

private:
    Mage* mage;
};
