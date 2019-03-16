#ifndef MAGESPELLS_H
#define MAGESPELLS_H

#include "CharacterSpells.h"

class Mage;

class MageSpells: public CharacterSpells {
public:
    MageSpells(Mage *mage);
    virtual ~MageSpells() override;

private:
    Mage* mage;
};

#endif // MAGESPELLS_H
