#ifndef SHAMANSPELLS_H
#define SHAMANSPELLS_H

#include "Spells.h"

class Shaman;

class ShamanSpells: public Spells {
    Q_OBJECT

public:
    ShamanSpells(Shaman *pchar);
    virtual ~ShamanSpells() override;

    void reset() override;

private:
    Shaman* pchar;
};

#endif // SHAMANSPELLS_H
