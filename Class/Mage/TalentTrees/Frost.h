#pragma once

#include "TalentTree.h"

class Mage;
class MageSpells;

class Frost: public TalentTree {
public:
    Frost(Mage* mage);
    ~Frost() override = default;

private:
    Mage* mage;
    MageSpells* spells;

    void add_improved_blizzard(QMap<QString, Talent*>& talent_tier);
};
