#ifndef SHAMANSPELLS_H
#define SHAMANSPELLS_H

#include "CharacterSpells.h"

class Buff;
class Shaman;

class ShamanSpells: public CharacterSpells {
public:
    ShamanSpells(Shaman *shaman);
    ~ShamanSpells() override;

    Buff* get_flurry() const;

private:
    Shaman* shaman;
    Buff* flurry;
};

#endif // SHAMANSPELLS_H
