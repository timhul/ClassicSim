#ifndef SHAMANSPELLS_H
#define SHAMANSPELLS_H

#include "CharacterSpells.h"

class Shaman;

class ShamanSpells: public CharacterSpells {
public:
    ShamanSpells(Shaman *shaman);

private:
    Shaman* shaman;
};

#endif // SHAMANSPELLS_H
