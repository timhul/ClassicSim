#ifndef MAGESPELLS_H
#define MAGESPELLS_H

#include "Spells.h"

class Mage;

class MageSpells: public Spells {
    Q_OBJECT

public:
    MageSpells(Mage *mage);
    virtual ~MageSpells() override;

    void reset() override;

private:
    Mage* mage;
};

#endif // MAGESPELLS_H
