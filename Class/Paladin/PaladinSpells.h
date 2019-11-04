#pragma once

#include "CharacterSpells.h"

class Paladin;
class PaladinSeal;

class PaladinSpells: public CharacterSpells {
public:
    PaladinSpells(Paladin *paladin);

    void apply_seal(PaladinSeal* new_seal);
    PaladinSeal* get_active_seal() const;

private:
    Paladin* paladin;
    PaladinSeal* active_seal {nullptr};
};
