#ifndef HUNTERSPELLS_H
#define HUNTERSPELLS_H

#include "CharacterSpells.h"

class Hunter;

class HunterSpells: public CharacterSpells {
public:
    HunterSpells(Hunter *hunter);
    virtual ~HunterSpells() override;

private:
    Hunter* hunter;
};

#endif // HUNTERSPELLS_H
