#ifndef SHAMANSPELLS_H
#define SHAMANSPELLS_H

#include "Spells.h"

class Shaman;

class ShamanSpells: public Spells {
public:
    ShamanSpells(Shaman *shaman);
    virtual ~ShamanSpells() override;

private:
    Shaman* shaman;
};

#endif // SHAMANSPELLS_H
