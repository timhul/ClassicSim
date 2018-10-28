#ifndef MAGESPELLS_H
#define MAGESPELLS_H

#include "Spells.h"

class Mage;

class MageSpells: public Spells {
public:
    MageSpells(Mage *mage);
    virtual ~MageSpells() override;

private:
    Mage* mage;
};

#endif // MAGESPELLS_H
