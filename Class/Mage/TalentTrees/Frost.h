#pragma once

#include "TalentTree.h"

class Mage;
class MageSpells;

class Frost: public TalentTree {
public:
    Frost(Mage* mage);

private:
    Mage* mage;
    MageSpells* spells;

    void add_improved_frostbolt(QMap<QString, Talent*>& talent_tier);
    void add_elemental_precision(QMap<QString, Talent*>& talent_tier);
    void add_ice_shards(QMap<QString, Talent*>& talent_tier);
    void add_piercing_ice(QMap<QString, Talent*>& talent_tier);
    void add_improved_blizzard(QMap<QString, Talent*>& talent_tier);
    void add_frost_channeling(QMap<QString, Talent*>& talent_tier);
    void add_winters_chill(QMap<QString, Talent*>& talent_tier);
};
