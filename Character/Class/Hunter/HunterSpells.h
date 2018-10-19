#ifndef HUNTERSPELLS_H
#define HUNTERSPELLS_H

#include "Spells.h"

class Hunter;

class HunterSpells: public Spells {
    Q_OBJECT

public:
    HunterSpells(Hunter *hunter);
    virtual ~HunterSpells() override;

private:
    Hunter* hunter;
};

#endif // HUNTERSPELLS_H
