#pragma once

#include "TalentTree.h"

class Mage;
class MageSpells;

class Fire : public TalentTree {
public:
    Fire(Mage* mage);

private:
    Mage* mage;
    MageSpells* spells;

    void add_improved_scorch(QMap<QString, Talent*>& talent_tier);
    void add_improved_fireball(QMap<QString, Talent*>& talent_tier);
    void add_ignite(QMap<QString, Talent*>& talent_tier);
    void add_incinerate(QMap<QString, Talent*>& talent_tier);
    void add_master_of_elements(QMap<QString, Talent*>& talent_tier);
    void add_critical_mass(QMap<QString, Talent*>& talent_tier);
    void add_fire_power(QMap<QString, Talent*>& talent_tier);
    void add_combustion(QMap<QString, Talent*>& talent_tier);
};
