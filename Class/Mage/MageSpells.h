#pragma once

#include "CharacterSpells.h"

class ClearcastingMage;
class Combustion;
class Ignite;
class Mage;
class Proc;

class MageSpells: public CharacterSpells {
public:
    MageSpells(Mage* mage);
    ~MageSpells() override;

    Combustion* get_combustion() const;
    Proc* get_clearcasting() const;

    void inflict_ignite(const double damage);
    bool clearcasting_active() const;
    void roll_clearcasting();

private:
    Mage* mage;

    ClearcastingMage* clearcasting;
    Combustion* combustion;
    Ignite* ignite;
};
