#ifndef HUNTERSPELLS_H
#define HUNTERSPELLS_H

#include "Spells.h"

class Hunter;

class HunterSpells: public Spells {
    Q_OBJECT

public:
    HunterSpells(Hunter *pchar);
    virtual ~HunterSpells() override;

    void reset() override;

private:
    Hunter* pchar;
};

#endif // HUNTERSPELLS_H
