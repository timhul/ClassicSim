#pragma once

#include "CharacterSpells.h"

class Warlock;

class WarlockSpells : public CharacterSpells {
public:
    WarlockSpells(Warlock* warlock);

private:
    Warlock* warlock;
};
