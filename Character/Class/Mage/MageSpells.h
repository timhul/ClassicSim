#ifndef MAGESPELLS_H
#define MAGESPELLS_H

#include "Spells.h"

class Mage;

class MageSpells: public Spells {
    Q_OBJECT

public:
    MageSpells(Mage *pchar);
    virtual ~MageSpells() override;

    void reset() override;

private:
    Mage* pchar;
};

#endif // MAGESPELLS_H
