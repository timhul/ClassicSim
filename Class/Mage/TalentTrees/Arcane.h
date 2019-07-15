#pragma once

#include "TalentTree.h"

class Mage;
class MageSpells;

class Arcane: public TalentTree {
public:
    Arcane(Mage* mage);

private:
    Mage* mage;
    MageSpells* spells;

    void add_arcane_subtlety(QMap<QString, Talent*>& talent_tier);
    void add_arcane_focus(QMap<QString, Talent*>& talent_tier);
    void add_arcane_concentration(QMap<QString, Talent*>& talent_tier);
    void add_arcane_meditation(QMap<QString, Talent*>& talent_tier);
    void add_arcane_mind(QMap<QString, Talent*>& talent_tier);
    void add_arcane_instability(QMap<QString, Talent*>& talent_tier);
};
