#pragma once

#include "TalentTree.h"

class Mage;
class MageSpells;

class Fire: public TalentTree {
public:
    Fire(Mage* mage);
    ~Fire() override = default;

    Talent* improved_fireball();

private:
    Mage* mage;
    MageSpells* spells;

    Talent* improved_scorch();
};
